/*
 * Copyright (C) 2017 Swift Navigation Inc.
 * Contact: Swift Navigation <dev@swiftnav.com>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#include <unistd.h>
#include <curl/curl.h>
#include <libpiksi/logging.h>
#include <libpiksi/util.h>

#include "libnetwork.h"

typedef struct {
  curl_off_t bytes;
  curl_off_t count;
  bool debug;
} network_xfer_t;

static size_t network_download_write(char *buf, size_t size, size_t n, void *data)
{
  const network_config_t *config = data;

  while (true) {
    ssize_t ret = write(config->fd, buf, size * n);
    if (ret < 0 && errno == EINTR) {
      continue;
    }

    if (config->debug) {
      piksi_log(LOG_DEBUG, "write bytes (%d) %d", size * n, ret);
    }

    return ret;
  }

  return -1;
}

static size_t network_upload_read(char *buf, size_t size, size_t n, void *data)
{
  const network_config_t *config = data;

  while (true) {
    ssize_t ret = read(config->fd, buf, size * n);
    if (ret < 0 && errno == EINTR) {
      continue;
    }

    if (config->debug) {
      piksi_log(LOG_DEBUG, "read bytes %d", ret);
    }

    if (ret < 0) {
      return CURL_READFUNC_ABORT;
    }

    return ret;
  }

  return -1;
}

static int network_download_xfer(void *data, curl_off_t dltot, curl_off_t dlnow, curl_off_t ultot, curl_off_t ulnow)
{
  (void)dltot;
  (void)ultot;
  (void)ulnow;

  network_xfer_t *xfer = data;

  if (xfer->debug) {
    piksi_log(LOG_DEBUG, "down bytes (%lld) %lld count %lld", dlnow, xfer->bytes, xfer->count);
  }

  if (xfer->bytes != dlnow) {
    xfer->bytes = dlnow;
    xfer->count = 0;
  }

  if (xfer->count++ > 30) {
    return -1;
  }

  return 0;
}

static int network_upload_xfer(void *data, curl_off_t dltot, curl_off_t dlnow, curl_off_t ultot, curl_off_t ulnow)
{
  (void)dltot;
  (void)dlnow;
  (void)ultot;

  network_xfer_t *xfer = data;

  if (xfer->debug) {
    piksi_log(LOG_DEBUG, "up bytes (%lld) %lld count %lld", ulnow, xfer->bytes, xfer->count);
  }

  if (xfer->bytes != ulnow) {
    xfer->bytes = ulnow;
    xfer->count = 0;
  }

  if (xfer->count++ > 30) {
    return -1;
  }

  return 0;
}

void ntrip_download(const network_config_t *config)
{
  network_xfer_t xfer = {
    .bytes = 0,
    .count = 0,
    .debug = config->debug,
  };

  CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
  if (code != CURLE_OK) {
    piksi_log(LOG_ERR, "global init %d", code);
    return;
  }

  CURL *curl = curl_easy_init();
  if (curl == NULL) {
    piksi_log(LOG_ERR, "init");
    curl_global_cleanup();
    return;
  }

  struct curl_slist *chunk = NULL;
  chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
  chunk = curl_slist_append(chunk, "Ntrip-Version: Ntrip/2.0");

  char error_buf[CURL_ERROR_SIZE];
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER,       chunk);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER,      error_buf);
  curl_easy_setopt(curl, CURLOPT_URL,              config->url);
  curl_easy_setopt(curl, CURLOPT_USERAGENT,        "NTRIP ntrip-client/1.0");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,    network_download_write);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA,        config);
  curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, network_download_xfer);
  curl_easy_setopt(curl, CURLOPT_XFERINFODATA,     &xfer);
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS,       0L);

  while (true) {
    code = curl_easy_perform(curl);
    piksi_log(LOG_INFO, "curl request (%d) \"%s\"", code, error_buf);
    usleep(1000000);
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();
}

void skylark_download(const network_config_t *config)
{
  network_xfer_t xfer = {
    .bytes = 0,
    .count = 0,
    .debug = config->debug,
  };

  char uuid_buf[256];
  if (device_uuid_get(uuid_buf, sizeof(uuid_buf)) != 0) {
    piksi_log(LOG_ERR, "device uuid error");
    return;
  }

  char device_buf[256];
  snprintf(device_buf, sizeof(device_buf), "Device-Uid: %s", uuid_buf);

  CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
  if (code != CURLE_OK) {
    piksi_log(LOG_ERR, "global init %d", code);
    return;
  }

  CURL *curl = curl_easy_init();
  if (curl == NULL) {
    piksi_log(LOG_ERR, "init");
    curl_global_cleanup();
    return;
  }

  struct curl_slist *chunk = NULL;
  chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
  chunk = curl_slist_append(chunk, "Accept: application/vnd.swiftnav.broker.v1+sbp2");
  chunk = curl_slist_append(chunk, device_buf);

  char error_buf[CURL_ERROR_SIZE];
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER,       chunk);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER,      error_buf);
  curl_easy_setopt(curl, CURLOPT_URL,              config->url);
  curl_easy_setopt(curl, CURLOPT_USERAGENT,        "skylark-agent/1.0");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,    network_download_write);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA,        config);
  curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, network_download_xfer);
  curl_easy_setopt(curl, CURLOPT_XFERINFODATA,     &xfer);
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS,       0L);

  while (true) {
    code = curl_easy_perform(curl);
    piksi_log(LOG_INFO, "curl request (%d) \"%s\"", code, error_buf);
    usleep(1000000);
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();
}

void skylark_upload(const network_config_t *config)
{
  network_xfer_t xfer = {
    .bytes = 0,
    .count = 0,
    .debug = config->debug,
  };

  char uuid_buf[256];
  if (device_uuid_get(uuid_buf, sizeof(uuid_buf)) != 0) {
    piksi_log(LOG_ERR, "device uuid error");
    return;
  }

  char device_buf[256];
  snprintf(device_buf, sizeof(device_buf), "Device-Uid: %s", uuid_buf);

  CURLcode code = curl_global_init(CURL_GLOBAL_ALL);
  if (code != CURLE_OK) {
    piksi_log(LOG_ERR, "global init %d", code);
    return;
  }

  CURL *curl = curl_easy_init();
  if (curl == NULL) {
    piksi_log(LOG_ERR, "init");
    curl_global_cleanup();
    return;
  }

  struct curl_slist *chunk = NULL;
  chunk = curl_slist_append(chunk, "Transfer-Encoding: chunked");
  chunk = curl_slist_append(chunk, "Content-Type: application/vnd.swiftnav.broker.v1+sbp2");
  chunk = curl_slist_append(chunk, device_buf);

  char error_buf[CURL_ERROR_SIZE];
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER,       chunk);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER,      error_buf);
  curl_easy_setopt(curl, CURLOPT_URL,              config->url);
  curl_easy_setopt(curl, CURLOPT_USERAGENT,        "skylark-agent/1.0");
  curl_easy_setopt(curl, CURLOPT_READFUNCTION,     network_upload_read);
  curl_easy_setopt(curl, CURLOPT_READDATA,         config);
  curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, network_upload_xfer);
  curl_easy_setopt(curl, CURLOPT_XFERINFODATA,     &xfer);
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS,       0L);
  curl_easy_setopt(curl, CURLOPT_PUT,              1L);

  while (true) {
    code = curl_easy_perform(curl);
    piksi_log(LOG_INFO, "curl request (%d) \"%s\"", code, error_buf);
    usleep(1000000);
  }

  curl_easy_cleanup(curl);
  curl_global_cleanup();
}
