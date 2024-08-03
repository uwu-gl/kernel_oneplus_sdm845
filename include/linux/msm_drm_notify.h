/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2017-2019, The Linux Foundation. All rights reserved.
 */
#ifndef _MSM_DRM_NOTIFY_H_
#define _MSM_DRM_NOTIFY_H_

#include <linux/notifier.h>

/* A hardware display blank change occurred */
#define MSM_DRM_EVENT_BLANK			0x01
/* A hardware display blank early change occurred */
#define MSM_DRM_EARLY_EVENT_BLANK		0x02
#ifdef VENDOR_EDIT
/* event for onscreenfingerprint scene */
#define MSM_DRM_ONSCREENFINGERPRINT_EVENT	0x10
#endif /* VENDOR_EDIT */

enum {
	/* panel: power on */
	MSM_DRM_BLANK_UNBLANK,
	/* panel: power off */
	MSM_DRM_BLANK_POWERDOWN,
	/* panel: power on for tp*/
	MSM_DRM_BLANK_UNBLANK_CUST,
	/* panel: lcd doze mode */
	MSM_DRM_BLANK_NORMAL,
	/* panel: power off */
	MSM_DRM_BLANK_POWERDOWN_CUST,
	/* panel: fingerprit on display */
	MSM_DRM_ONSCREENFINGERPRINT_EVENT,
};

enum msm_drm_display_id {
	/* primary display */
	MSM_DRM_PRIMARY_DISPLAY,
	/* external display */
	MSM_DRM_EXTERNAL_DISPLAY,
	MSM_DRM_DISPLAY_MAX
};

struct msm_drm_notifier {
	enum msm_drm_display_id id;
	void *data;
};

extern int msm_drm_register_client(struct notifier_block *nb);
extern int msm_drm_unregister_client(struct notifier_block *nb);
#endif
