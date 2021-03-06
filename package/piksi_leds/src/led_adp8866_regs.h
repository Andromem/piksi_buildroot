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

#ifndef SWIFTNAV_LED_ADP8866_REGS_H
#define SWIFTNAV_LED_ADP8866_REGS_H

#include <stdint.h>

/* Registers */
#define LED_ADP8866_REG_MFDVID (0x00U)
#define LED_ADP8866_REG_MDCR (0x01U)

#define LED_ADP8866_REG_LVL_SEL1 (0x07U)
#define LED_ADP8866_REG_LVL_SEL2 (0x08U)

#define LED_ADP8866_REG_CFGR (0x10U)
#define LED_ADP8866_REG_BLSEL (0x11U)

#define LED_ADP8866_REG_ISCC1 (0x1AU)
#define LED_ADP8866_REG_ISCC2 (0x1BU)

/* Bitfields */
#define LED_ADP8866_MFDVID_DVID_Pos (0U)
#define LED_ADP8866_MFDVID_DVID_Msk (0xfU << LED_ADP8866_MFDVID_DVID_Pos)
#define LED_ADP8866_MFDVID_DVID (0x03U)

#define LED_ADP8866_MFDVID_MFID_Pos (4U)
#define LED_ADP8866_MFDVID_MFID_Msk (0xfU << LED_ADP8866_MFDVID_MFID_Pos)
#define LED_ADP8866_MFDVID_MFID (0x05U)

#define LED_ADP8866_MDCR_BL_EN_Pos (0U)
#define LED_ADP8866_MDCR_BL_EN_Msk (0x1U << LED_ADP8866_MDCR_BL_EN_Pos)

#define LED_ADP8866_MDCR_SIS_EN_Pos (2U)
#define LED_ADP8866_MDCR_SIS_EN_Msk (0x1U << LED_ADP8866_MDCR_SIS_EN_Pos)

#define LED_ADP8866_MDCR_GDWN_DIS_Pos (3U)
#define LED_ADP8866_MDCR_GDWN_DIS_Msk (0x1U << LED_ADP8866_MDCR_GDWN_DIS_Pos)

#define LED_ADP8866_MDCR_ALT_GSEL_Pos (4U)
#define LED_ADP8866_MDCR_ALT_GSEL_Msk (0x1U << LED_ADP8866_MDCR_ALT_GSEL_Pos)

#define LED_ADP8866_MDCR_NSTBY_Pos (5U)
#define LED_ADP8866_MDCR_NSTBY_Msk (0x1U << LED_ADP8866_MDCR_NSTBY_Pos)

#define LED_ADP8866_MDCR_INT_CFG_Pos (6U)
#define LED_ADP8866_MDCR_INT_CFG_Msk (0x1U << LED_ADP8866_MDCR_INT_CFG_Pos)

#define LED_ADP8866_LVL_SEL1_LEVEL_SET_Pos (0U)
#define LED_ADP8866_LVL_SEL1_LEVEL_SET_Msk \
  (0x3fU << LED_ADP8866_LVL_SEL1_LEVEL_SET_Pos)

#define LED_ADP8866_LVL_SEL1_D9LVL_Pos (6U)
#define LED_ADP8866_LVL_SEL1_D9LVL_Msk (0x1U << LED_ADP8866_LVL_SEL1_D9LVL_Pos)

#define LED_ADP8866_LVL_SEL2_D1LVL_Pos (0U)
#define LED_ADP8866_LVL_SEL2_D1LVL_Msk (0x1U << LED_ADP8866_LVL_SEL2_D1LVL_Pos)

#define LED_ADP8866_LVL_SEL2_D2LVL_Pos (1U)
#define LED_ADP8866_LVL_SEL2_D2LVL_Msk (0x1U << LED_ADP8866_LVL_SEL2_D2LVL_Pos)

#define LED_ADP8866_LVL_SEL2_D3LVL_Pos (2U)
#define LED_ADP8866_LVL_SEL2_D3LVL_Msk (0x1U << LED_ADP8866_LVL_SEL2_D3LVL_Pos)

#define LED_ADP8866_LVL_SEL2_D4LVL_Pos (3U)
#define LED_ADP8866_LVL_SEL2_D4LVL_Msk (0x1U << LED_ADP8866_LVL_SEL2_D4LVL_Pos)

#define LED_ADP8866_LVL_SEL2_D5LVL_Pos (4U)
#define LED_ADP8866_LVL_SEL2_D5LVL_Msk (0x1U << LED_ADP8866_LVL_SEL2_D5LVL_Pos)

#define LED_ADP8866_LVL_SEL2_D6LVL_Pos (5U)
#define LED_ADP8866_LVL_SEL2_D6LVL_Msk (0x1U << LED_ADP8866_LVL_SEL2_D6LVL_Pos)

#define LED_ADP8866_LVL_SEL2_D7LVL_Pos (6U)
#define LED_ADP8866_LVL_SEL2_D7LVL_Msk (0x1U << LED_ADP8866_LVL_SEL2_D7LVL_Pos)

#define LED_ADP8866_LVL_SEL2_D8LVL_Pos (7U)
#define LED_ADP8866_LVL_SEL2_D8LVL_Msk (0x1U << LED_ADP8866_LVL_SEL2_D8LVL_Pos)

#define LED_ADP8866_LVL_SEL_NORMAL (0x0U)
#define LED_ADP8866_LVL_SEL_SCALED (0x1U)

#define LED_ADP8866_CFGR_BL_LAW_Pos (1U)
#define LED_ADP8866_CFGR_BL_LAW_Msk (0x3U << LED_ADP8866_CFGR_BL_LAW_Pos)

#define LED_ADP8866_CFGR_CABCFADE_Pos (3U)
#define LED_ADP8866_CFGR_CABCFADE_Msk (0x1U << LED_ADP8866_CFGR_CABCFADE_Pos)

#define LED_ADP8866_CFGR_D9SEL_Pos (4U)
#define LED_ADP8866_CFGR_D9SEL_Msk (0x1U << LED_ADP8866_CFGR_D9SEL_Pos)

#define LED_ADP8866_BLSEL_D1SEL_Pos (0U)
#define LED_ADP8866_BLSEL_D1SEL_Msk (0x1U << LED_ADP8866_BLSEL_D1SEL_Pos)

#define LED_ADP8866_BLSEL_D2SEL_Pos (1U)
#define LED_ADP8866_BLSEL_D2SEL_Msk (0x1U << LED_ADP8866_BLSEL_D2SEL_Pos)

#define LED_ADP8866_BLSEL_D3SEL_Pos (2U)
#define LED_ADP8866_BLSEL_D3SEL_Msk (0x1U << LED_ADP8866_BLSEL_D3SEL_Pos)

#define LED_ADP8866_BLSEL_D4SEL_Pos (3U)
#define LED_ADP8866_BLSEL_D4SEL_Msk (0x1U << LED_ADP8866_BLSEL_D4SEL_Pos)

#define LED_ADP8866_BLSEL_D5SEL_Pos (4U)
#define LED_ADP8866_BLSEL_D5SEL_Msk (0x1U << LED_ADP8866_BLSEL_D5SEL_Pos)

#define LED_ADP8866_BLSEL_D6SEL_Pos (5U)
#define LED_ADP8866_BLSEL_D6SEL_Msk (0x1U << LED_ADP8866_BLSEL_D6SEL_Pos)

#define LED_ADP8866_BLSEL_D7SEL_Pos (6U)
#define LED_ADP8866_BLSEL_D7SEL_Msk (0x1U << LED_ADP8866_BLSEL_D7SEL_Pos)

#define LED_ADP8866_BLSEL_D8SEL_Pos (7U)
#define LED_ADP8866_BLSEL_D8SEL_Msk (0x1U << LED_ADP8866_BLSEL_D8SEL_Pos)

#define LED_ADP8866_BLSEL_BL (0x0U)
#define LED_ADP8866_BLSEL_IS (0x1U)

#define LED_ADP8866_ISCC1_SC_LAW_Pos (0U)
#define LED_ADP8866_ISCC1_SC_LAW_Msk (0x3U << LED_ADP8866_ISCC1_SC_LAW_Pos)

#define LED_ADP8866_ISCC1_SC9_EN_Pos (2U)
#define LED_ADP8866_ISCC1_SC9_EN_Msk (0x1U << LED_ADP8866_ISCC1_SC9_EN_Pos)

#define LED_ADP8866_ISCC2_SC1_EN_Pos (0U)
#define LED_ADP8866_ISCC2_SC1_EN_Msk (0x1U << LED_ADP8866_ISCC2_SC1_EN_Pos)

#define LED_ADP8866_ISCC2_SC2_EN_Pos (1U)
#define LED_ADP8866_ISCC2_SC2_EN_Msk (0x1U << LED_ADP8866_ISCC2_SC2_EN_Pos)

#define LED_ADP8866_ISCC2_SC3_EN_Pos (2U)
#define LED_ADP8866_ISCC2_SC3_EN_Msk (0x1U << LED_ADP8866_ISCC2_SC3_EN_Pos)

#define LED_ADP8866_ISCC2_SC4_EN_Pos (3U)
#define LED_ADP8866_ISCC2_SC4_EN_Msk (0x1U << LED_ADP8866_ISCC2_SC4_EN_Pos)

#define LED_ADP8866_ISCC2_SC5_EN_Pos (4U)
#define LED_ADP8866_ISCC2_SC5_EN_Msk (0x1U << LED_ADP8866_ISCC2_SC5_EN_Pos)

#define LED_ADP8866_ISCC2_SC6_EN_Pos (5U)
#define LED_ADP8866_ISCC2_SC6_EN_Msk (0x1U << LED_ADP8866_ISCC2_SC6_EN_Pos)

#define LED_ADP8866_ISCC2_SC7_EN_Pos (6U)
#define LED_ADP8866_ISCC2_SC7_EN_Msk (0x1U << LED_ADP8866_ISCC2_SC7_EN_Pos)

#define LED_ADP8866_ISCC2_SC8_EN_Pos (7U)
#define LED_ADP8866_ISCC2_SC8_EN_Msk (0x1U << LED_ADP8866_ISCC2_SC8_EN_Pos)

#define LED_ADP8866_ISCn_SCDn_Pos (0U)
#define LED_ADP8866_ISCn_SCDn_Msk (0x7fU << LED_ADP8866_ISCn_SCDn_Pos)

#endif /* SWIFTNAV_LED_ADP8866_REGS_H */
