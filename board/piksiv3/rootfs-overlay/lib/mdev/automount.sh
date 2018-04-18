#!/bin/ash

destdir=/media
log_tag=automount

source /etc/init.d/logging.sh

do_umount()
{
  local devname=$1; shift

  local mountpoint="${destdir}/${devname}"
  local dev="/dev/${devname}"

  if grep -qs "^${dev} " /proc/mounts; then
    logi "Unmounting '${dev}' from '${mountpoint}'"
    umount -f "${mountpoint}";
  fi

  [[ -d "${mountpoint}" ]] && rmdir "${mountpoint}"
}

do_mount()
{
  local devname=$1; shift

  local mountpoint="${destdir}/${devname}"
  local dev="/dev/${devname}"

  logi "Mounting '${dev}' to '${mountpoint}'"

  mkdir -p $mountpoint || exit 1

  if ! mount -t auto $dev $mountpoint 1>$logger_stdout 2>$logger_stderr; then
    loge "Mount failed, cleaning up mount point..."
    rmdir $mountpoint
    exit 1
  fi
}

if [[ -f /var/run/automount_disabled ]]; then
  logd "Disabled..."
  exit 0
fi

logd "Invoked..."

case "${ACTION}" in
add|"")
  logd "Card added..."
  do_umount ${MDEV}
  do_mount ${MDEV}
  ;;
remove)
  logd "Card removed..."
  do_umount ${MDEV}
  ;;
esac
