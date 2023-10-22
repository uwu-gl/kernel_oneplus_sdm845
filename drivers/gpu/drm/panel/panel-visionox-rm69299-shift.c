// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2023 Caleb Connolly <caleb.connolly@linaro.org>
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2016-2017, The Linux Foundation. All rights reserved.

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/regulator/consumer.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct shift6mq_rm69299 {
	struct drm_panel panel;
	struct regulator_bulk_data supplies[2];
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
	bool prepared;
};

static inline
struct shift6mq_rm69299 *to_shift6mq_rm69299(struct drm_panel *panel)
{
	return container_of(panel, struct shift6mq_rm69299, panel);
}

static void shift6mq_rm69299_reset(struct shift6mq_rm69299 *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	msleep(20);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	msleep(20);
}

static int shift6mq_rm69299_on(struct shift6mq_rm69299 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x05, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x06, 0x08);
	mipi_dsi_dcs_write_seq(dsi, 0x08, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x09, 0x08);
	mipi_dsi_dcs_write_seq(dsi, 0x0a, 0x07);
	mipi_dsi_dcs_write_seq(dsi, 0x0b, 0xcc);
	mipi_dsi_dcs_write_seq(dsi, 0x0c, 0x07);
	mipi_dsi_dcs_write_seq(dsi, 0x0d, 0x90);
	mipi_dsi_dcs_write_seq(dsi, 0x0f, 0x87);
	mipi_dsi_dcs_write_seq(dsi, 0x20, 0x8d);
	mipi_dsi_dcs_write_seq(dsi, 0x21, 0x8d);
	mipi_dsi_dcs_write_seq(dsi, 0x24, 0x05);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_GAMMA_CURVE, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x28, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x2a, 0x05);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_LUT, 0x28);
	mipi_dsi_dcs_write_seq(dsi, 0x2f, 0x28);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_ROWS, 0x32);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_COLUMNS, 0x32);
	mipi_dsi_dcs_write_seq(dsi, 0x37, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0x38, 0x30);
	mipi_dsi_dcs_write_seq(dsi, 0x39, 0xa8);
	mipi_dsi_dcs_write_seq(dsi, 0x46, 0x48);
	mipi_dsi_dcs_write_seq(dsi, 0x47, 0x48);
	mipi_dsi_dcs_write_seq(dsi, 0x6b, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0x6f, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x74, 0x2b);
	mipi_dsi_dcs_write_seq(dsi, 0x80, 0x1c);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x93, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0x16, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x85, 0x07);
	mipi_dsi_dcs_write_seq(dsi, 0x84, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x86, 0x0f);
	mipi_dsi_dcs_write_seq(dsi, 0x87, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x8c, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x88, 0x2e);
	mipi_dsi_dcs_write_seq(dsi, 0x89, 0x2e);
	mipi_dsi_dcs_write_seq(dsi, 0x8b, 0x09);
	mipi_dsi_dcs_write_seq(dsi, 0x95, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x91, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x90, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x8d, 0xd0);
	mipi_dsi_dcs_write_seq(dsi, 0x8a, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0xa0);
	mipi_dsi_dcs_write_seq(dsi, 0x13, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x33, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x0b, 0x33);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_ADDRESS_MODE, 0x1e);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_COLUMNS, 0x88);
	mipi_dsi_dcs_write_seq(dsi, 0x32, 0x88);
	mipi_dsi_dcs_write_seq(dsi, 0x37, 0xf1);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x50);
	mipi_dsi_dcs_write_seq(dsi, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x01, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x02, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x03, 0x7c);
	mipi_dsi_dcs_write_seq(dsi, 0x04, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x05, 0x7c);
	mipi_dsi_dcs_write_seq(dsi, 0x06, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x07, 0x8e);
	mipi_dsi_dcs_write_seq(dsi, 0x08, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x09, 0xd3);
	mipi_dsi_dcs_write_seq(dsi, 0x0a, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x0b, 0xfd);
	mipi_dsi_dcs_write_seq(dsi, 0x0c, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x0d, 0x22);
	mipi_dsi_dcs_write_seq(dsi, 0x0e, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x0f, 0x5e);
	mipi_dsi_dcs_write_seq(dsi, 0x10, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x11, 0x99);
	mipi_dsi_dcs_write_seq(dsi, 0x12, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x13, 0xd3);
	mipi_dsi_dcs_write_seq(dsi, 0x14, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x15, 0xf3);
	mipi_dsi_dcs_write_seq(dsi, 0x16, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x17, 0x33);
	mipi_dsi_dcs_write_seq(dsi, 0x18, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x19, 0x72);
	mipi_dsi_dcs_write_seq(dsi, 0x1a, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x1b, 0xa5);
	mipi_dsi_dcs_write_seq(dsi, 0x1c, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x1d, 0xd7);
	mipi_dsi_dcs_write_seq(dsi, 0x1e, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x1f, 0x09);
	mipi_dsi_dcs_write_seq(dsi, 0x20, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x21, 0x41);
	mipi_dsi_dcs_write_seq(dsi, 0x22, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x23, 0x79);
	mipi_dsi_dcs_write_seq(dsi, 0x24, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x25, 0xb1);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_GAMMA_CURVE, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x27, 0xcc);
	mipi_dsi_dcs_write_seq(dsi, 0x28, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x29, 0xe8);
	mipi_dsi_dcs_write_seq(dsi, 0x2a, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x2b, 0x04);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_ROWS, 0x05);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_COLUMNS, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0x32, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x33, 0x3c);
	mipi_dsi_dcs_write_seq(dsi, 0x34, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x35, 0x58);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_ADDRESS_MODE, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x37, 0x73);
	mipi_dsi_dcs_write_seq(dsi, 0x38, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x39, 0x8f);

	ret = mipi_dsi_dcs_set_pixel_format(dsi, 0x05);
	if (ret < 0) {
		dev_err(dev, "Failed to set pixel format: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0x3b, 0x9d);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_VSYNC_TIMING, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x41, 0xab);
	mipi_dsi_dcs_write_seq(dsi, 0x42, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x43, 0xb2);
	mipi_dsi_dcs_write_seq(dsi, 0x44, 0x05);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_GET_SCANLINE, 0xb5);
	mipi_dsi_dcs_write_seq(dsi, 0x46, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x47, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x48, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x49, 0x7c);
	mipi_dsi_dcs_write_seq(dsi, 0x4a, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x4b, 0xae);
	mipi_dsi_dcs_write_seq(dsi, 0x4c, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x4d, 0xc6);
	mipi_dsi_dcs_write_seq(dsi, 0x4e, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x4f, 0xee);
	mipi_dsi_dcs_write_seq(dsi, 0x50, 0x02);

	ret = mipi_dsi_dcs_set_display_brightness(dsi, 0x0014);
	if (ret < 0) {
		dev_err(dev, "Failed to set display brightness: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0x52, 0x02);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x31);
	mipi_dsi_dcs_write_seq(dsi, 0x58, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x59, 0x68);
	mipi_dsi_dcs_write_seq(dsi, 0x5a, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x5b, 0x9f);
	mipi_dsi_dcs_write_seq(dsi, 0x5c, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x5d, 0xd5);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_CABC_MIN_BRIGHTNESS, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x5f, 0xf5);
	mipi_dsi_dcs_write_seq(dsi, 0x60, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x61, 0x33);
	mipi_dsi_dcs_write_seq(dsi, 0x62, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x63, 0x70);
	mipi_dsi_dcs_write_seq(dsi, 0x64, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x65, 0xa2);
	mipi_dsi_dcs_write_seq(dsi, 0x66, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x67, 0xd4);
	mipi_dsi_dcs_write_seq(dsi, 0x68, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x69, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x6a, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x6b, 0x3b);
	mipi_dsi_dcs_write_seq(dsi, 0x6c, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x6d, 0x71);
	mipi_dsi_dcs_write_seq(dsi, 0x6e, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x6f, 0xa7);
	mipi_dsi_dcs_write_seq(dsi, 0x70, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x71, 0xc2);
	mipi_dsi_dcs_write_seq(dsi, 0x72, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x73, 0xdc);
	mipi_dsi_dcs_write_seq(dsi, 0x74, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x75, 0xf7);
	mipi_dsi_dcs_write_seq(dsi, 0x76, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x77, 0x12);
	mipi_dsi_dcs_write_seq(dsi, 0x78, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x79, 0x2d);
	mipi_dsi_dcs_write_seq(dsi, 0x7a, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x7b, 0x48);
	mipi_dsi_dcs_write_seq(dsi, 0x7c, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x7d, 0x63);
	mipi_dsi_dcs_write_seq(dsi, 0x7e, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x7f, 0x7e);
	mipi_dsi_dcs_write_seq(dsi, 0x80, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x81, 0x8b);
	mipi_dsi_dcs_write_seq(dsi, 0x82, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x83, 0x98);
	mipi_dsi_dcs_write_seq(dsi, 0x84, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x85, 0x9f);
	mipi_dsi_dcs_write_seq(dsi, 0x86, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0x87, 0xa2);
	mipi_dsi_dcs_write_seq(dsi, 0x88, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x89, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x8a, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x8b, 0x7c);
	mipi_dsi_dcs_write_seq(dsi, 0x8c, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x8d, 0xae);
	mipi_dsi_dcs_write_seq(dsi, 0x8e, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x8f, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x90, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x91, 0x2e);
	mipi_dsi_dcs_write_seq(dsi, 0x92, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x93, 0x4e);
	mipi_dsi_dcs_write_seq(dsi, 0x94, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x95, 0x6e);
	mipi_dsi_dcs_write_seq(dsi, 0x96, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x97, 0xaa);
	mipi_dsi_dcs_write_seq(dsi, 0x98, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x99, 0xe5);
	mipi_dsi_dcs_write_seq(dsi, 0x9a, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x9b, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0x9c, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x9d, 0x41);
	mipi_dsi_dcs_write_seq(dsi, 0x9e, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0x9f, 0x84);
	mipi_dsi_dcs_write_seq(dsi, 0xa4, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0xa5, 0xc6);
	mipi_dsi_dcs_write_seq(dsi, 0xa6, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0xa7, 0xff);
	mipi_dsi_dcs_write_seq(dsi, 0xac, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0xad, 0x37);
	mipi_dsi_dcs_write_seq(dsi, 0xae, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0xaf, 0x6e);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0xb1, 0xac);
	mipi_dsi_dcs_write_seq(dsi, 0xb2, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0xb3, 0xe9);
	mipi_dsi_dcs_write_seq(dsi, 0xb4, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xb5, 0x26);
	mipi_dsi_dcs_write_seq(dsi, 0xb6, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xb7, 0x44);
	mipi_dsi_dcs_write_seq(dsi, 0xb8, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xb9, 0x63);
	mipi_dsi_dcs_write_seq(dsi, 0xba, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xbb, 0x81);
	mipi_dsi_dcs_write_seq(dsi, 0xbc, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0xa0);
	mipi_dsi_dcs_write_seq(dsi, 0xbe, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xbf, 0xbe);
	mipi_dsi_dcs_write_seq(dsi, 0xc0, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xc1, 0xdd);
	mipi_dsi_dcs_write_seq(dsi, 0xc2, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xc3, 0xfb);
	mipi_dsi_dcs_write_seq(dsi, 0xc4, 0x06);
	mipi_dsi_dcs_write_seq(dsi, 0xc5, 0x1a);
	mipi_dsi_dcs_write_seq(dsi, 0xc6, 0x06);
	mipi_dsi_dcs_write_seq(dsi, 0xc7, 0x29);
	mipi_dsi_dcs_write_seq(dsi, 0xc8, 0x06);
	mipi_dsi_dcs_write_seq(dsi, 0xc9, 0x38);
	mipi_dsi_dcs_write_seq(dsi, 0xca, 0x06);
	mipi_dsi_dcs_write_seq(dsi, 0xcb, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0xcc, 0x06);
	mipi_dsi_dcs_write_seq(dsi, 0xcd, 0x43);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x60);
	mipi_dsi_dcs_write_seq(dsi, 0x00, 0xcc);
	mipi_dsi_dcs_write_seq(dsi, 0x01, 0x0f);
	mipi_dsi_dcs_write_seq(dsi, 0x02, 0xff);
	mipi_dsi_dcs_write_seq(dsi, 0x03, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x04, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x05, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x06, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x07, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x09, 0xc4);
	mipi_dsi_dcs_write_seq(dsi, 0x0a, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x0b, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x0c, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x0d, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x0e, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x0f, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x10, 0x71);
	mipi_dsi_dcs_write_seq(dsi, 0x12, 0xc4);
	mipi_dsi_dcs_write_seq(dsi, 0x13, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x14, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x15, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x16, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x17, 0x06);
	mipi_dsi_dcs_write_seq(dsi, 0x18, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x19, 0x71);
	mipi_dsi_dcs_write_seq(dsi, 0x1b, 0xc4);
	mipi_dsi_dcs_write_seq(dsi, 0x1c, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x1d, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x1e, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x1f, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x20, 0x08);
	mipi_dsi_dcs_write_seq(dsi, 0x21, 0x66);
	mipi_dsi_dcs_write_seq(dsi, 0x22, 0xb4);
	mipi_dsi_dcs_write_seq(dsi, 0x24, 0xc4);
	mipi_dsi_dcs_write_seq(dsi, 0x25, 0x00);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_GAMMA_CURVE, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x27, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x28, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x29, 0x07);
	mipi_dsi_dcs_write_seq(dsi, 0x2a, 0x66);
	mipi_dsi_dcs_write_seq(dsi, 0x2b, 0xb4);
	mipi_dsi_dcs_write_seq(dsi, 0x2f, 0xc4);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_ROWS, 0x00);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_PARTIAL_COLUMNS, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x32, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0x33, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x34, 0x03);

	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	if (ret < 0) {
		dev_err(dev, "Failed to set tear on: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_ADDRESS_MODE, 0x71);
	mipi_dsi_dcs_write_seq(dsi, 0x38, 0xc4);
	mipi_dsi_dcs_write_seq(dsi, 0x39, 0x00);

	ret = mipi_dsi_dcs_set_pixel_format(dsi, 0x04);
	if (ret < 0) {
		dev_err(dev, "Failed to set pixel format: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0x3b, 0x01);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_3D_CONTROL, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x3f, 0x05);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_VSYNC_TIMING, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x41, 0x71);
	mipi_dsi_dcs_write_seq(dsi, 0x83, 0xce);
	mipi_dsi_dcs_write_seq(dsi, 0x84, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0x85, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0x86, 0xdc);
	mipi_dsi_dcs_write_seq(dsi, 0x87, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x88, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0x89, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x8a, 0xbb);
	mipi_dsi_dcs_write_seq(dsi, 0x8b, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0xc7, 0x0e);
	mipi_dsi_dcs_write_seq(dsi, 0xc8, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xc9, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xca, 0x06);
	mipi_dsi_dcs_write_seq(dsi, 0xcb, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xcc, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0xcd, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0xce, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xcf, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xd0, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xd1, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xd2, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xd3, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xd4, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xd5, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xd6, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xd7, 0x17);
	mipi_dsi_dcs_write_seq(dsi, 0xd8, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xd9, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0xda, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xdb, 0x0e);
	mipi_dsi_dcs_write_seq(dsi, 0xdc, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xdd, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xde, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0xdf, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xe0, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0xe1, 0x04);
	mipi_dsi_dcs_write_seq(dsi, 0xe2, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xe3, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xe4, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xe5, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xe6, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xe7, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xe8, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xe9, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xea, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xeb, 0x17);
	mipi_dsi_dcs_write_seq(dsi, 0xec, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xed, 0x16);
	mipi_dsi_dcs_write_seq(dsi, 0xee, 0x1f);
	mipi_dsi_dcs_write_seq(dsi, 0xef, 0x03);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x70);
	mipi_dsi_dcs_write_seq(dsi, 0x5a, 0x0b);
	mipi_dsi_dcs_write_seq(dsi, 0x5b, 0x0b);
	mipi_dsi_dcs_write_seq(dsi, 0x5c, 0x55);
	mipi_dsi_dcs_write_seq(dsi, 0x5d, 0x24);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x90);
	mipi_dsi_dcs_write_seq(dsi, 0x12, 0x24);
	mipi_dsi_dcs_write_seq(dsi, 0x13, 0x49);
	mipi_dsi_dcs_write_seq(dsi, 0x14, 0x92);
	mipi_dsi_dcs_write_seq(dsi, 0x15, 0x86);
	mipi_dsi_dcs_write_seq(dsi, 0x16, 0x61);
	mipi_dsi_dcs_write_seq(dsi, 0x17, 0x18);
	mipi_dsi_dcs_write_seq(dsi, 0x18, 0x24);
	mipi_dsi_dcs_write_seq(dsi, 0x19, 0x49);
	mipi_dsi_dcs_write_seq(dsi, 0x1a, 0x92);
	mipi_dsi_dcs_write_seq(dsi, 0x1b, 0x86);
	mipi_dsi_dcs_write_seq(dsi, 0x1c, 0x61);
	mipi_dsi_dcs_write_seq(dsi, 0x1d, 0x18);
	mipi_dsi_dcs_write_seq(dsi, 0x1e, 0x24);
	mipi_dsi_dcs_write_seq(dsi, 0x1f, 0x49);
	mipi_dsi_dcs_write_seq(dsi, 0x20, 0x92);
	mipi_dsi_dcs_write_seq(dsi, 0x21, 0x86);
	mipi_dsi_dcs_write_seq(dsi, 0x22, 0x61);
	mipi_dsi_dcs_write_seq(dsi, 0x23, 0x18);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x40);
	mipi_dsi_dcs_write_seq(dsi, 0x0e, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0xa0);
	mipi_dsi_dcs_write_seq(dsi, 0x04, 0x80);
	mipi_dsi_dcs_write_seq(dsi, 0x16, 0x00);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_SET_GAMMA_CURVE, 0x10);
	mipi_dsi_dcs_write_seq(dsi, 0x2f, 0x37);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0xd0);
	mipi_dsi_dcs_write_seq(dsi, 0x06, 0x0f);
	mipi_dsi_dcs_write_seq(dsi, 0x4b, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x56, 0x4a);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xc2, 0x08);

	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	if (ret < 0) {
		dev_err(dev, "Failed to set tear on: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x70);
	mipi_dsi_dcs_write_seq(dsi, 0x7d, 0x61);
	mipi_dsi_dcs_write_seq(dsi, 0x7f, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x7e, 0x4e);
	mipi_dsi_dcs_write_seq(dsi, 0x52, 0x2c);
	mipi_dsi_dcs_write_seq(dsi, 0x49, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x4a, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x4b, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x4c, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0x4d, 0xe8);
	mipi_dsi_dcs_write_seq(dsi, 0x4e, 0x25);
	mipi_dsi_dcs_write_seq(dsi, 0x4f, 0x6e);
	mipi_dsi_dcs_write_seq(dsi, 0x50, 0xae);

	ret = mipi_dsi_dcs_set_display_brightness(dsi, 0x002f);
	if (ret < 0) {
		dev_err(dev, "Failed to set display brightness: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0xad, 0xf4);
	mipi_dsi_dcs_write_seq(dsi, 0xae, 0x8f);
	mipi_dsi_dcs_write_seq(dsi, 0xaf, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x54);
	mipi_dsi_dcs_write_seq(dsi, 0xb1, 0x3a);
	mipi_dsi_dcs_write_seq(dsi, 0xb2, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb3, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb4, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb5, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb6, 0x18);
	mipi_dsi_dcs_write_seq(dsi, 0xb7, 0x30);
	mipi_dsi_dcs_write_seq(dsi, 0xb8, 0x4a);
	mipi_dsi_dcs_write_seq(dsi, 0xb9, 0x98);
	mipi_dsi_dcs_write_seq(dsi, 0xba, 0x30);
	mipi_dsi_dcs_write_seq(dsi, 0xbb, 0x60);
	mipi_dsi_dcs_write_seq(dsi, 0xbc, 0x50);
	mipi_dsi_dcs_write_seq(dsi, 0xbd, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xbe, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xbf, 0x39);
	mipi_dsi_dcs_write_seq(dsi, 0xfe, 0x00);

	ret = mipi_dsi_dcs_set_display_brightness(dsi, 0x00df);
	if (ret < 0) {
		dev_err(dev, "Failed to set display brightness: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}
	msleep(20);

	return 0;
}

static int shift6mq_rm69299_off(struct shift6mq_rm69299 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}
	msleep(20);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	return regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);;
}

static int shift6mq_rm69299_prepare(struct drm_panel *panel)
{
	struct shift6mq_rm69299 *ctx = to_shift6mq_rm69299(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	if (ctx->prepared)
		return 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret < 0)
		return ret;

	shift6mq_rm69299_reset(ctx);

	ret = shift6mq_rm69299_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	ctx->prepared = true;
	return 0;
}

static int shift6mq_rm69299_disable(struct drm_panel *panel)
{
	struct shift6mq_rm69299 *ctx = to_shift6mq_rm69299(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = shift6mq_rm69299_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	return 0;
}

static int shift6mq_rm69299_unprepare(struct drm_panel *panel)
{
	struct shift6mq_rm69299 *ctx = to_shift6mq_rm69299(panel);

	if (!ctx->prepared)
		return 0;

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	ctx->prepared = false;
	return 0;
}

static const struct drm_display_mode shift6mq_rm69299_mode = {
	.clock = (1080 + 26 + 2 + 36) * (2160 + 8 + 4 + 4) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 26,
	.hsync_end = 1080 + 26 + 2,
	.htotal = 1080 + 26 + 2 + 36,
	.vdisplay = 2160,
	.vsync_start = 2160 + 8,
	.vsync_end = 2160 + 8 + 4,
	.vtotal = 2160 + 8 + 4 + 4,
	.width_mm = 74,
	.height_mm = 131,
};

static int shift6mq_rm69299_get_modes(struct drm_panel *panel,
				      struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &shift6mq_rm69299_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs shift6mq_rm69299_panel_funcs = {
	.disable = shift6mq_rm69299_disable,
	.prepare = shift6mq_rm69299_prepare,
	.unprepare = shift6mq_rm69299_unprepare,
	.get_modes = shift6mq_rm69299_get_modes,
};

static int shift6mq_rm69299_panel_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	int ret;

	ret = mipi_dsi_dcs_set_display_brightness(dsi,
						backlight_get_brightness(bl));
	if (ret < 0)
		return ret;

	return 0;
}

static const struct backlight_ops shift6mq_rm69299_panel_bl_ops = {
	.update_status = shift6mq_rm69299_panel_bl_update_status,
};

static struct backlight_device *
shift6mq_rm69299_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_PLATFORM,
		.brightness = 50,
		.max_brightness = 255,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					&shift6mq_rm69299_panel_bl_ops, &props);
}

static int shift6mq_rm69299_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct shift6mq_rm69299 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	ctx->supplies[0].supply = "vdda";
	ctx->supplies[1].supply = "vdd3p3";

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies),
				      ctx->supplies);
	if (ret < 0)
		return ret;

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_NO_EOT_PACKET;

	drm_panel_init(&ctx->panel, dev, &shift6mq_rm69299_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.backlight = shift6mq_rm69299_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
				     "Failed to create backlight\n");
	ctx->panel.prepare_prev_first = true;

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to attach to DSI host: %d\n", ret);
		drm_panel_remove(&ctx->panel);
		return ret;
	}

	return 0;
}

static void shift6mq_rm69299_remove(struct mipi_dsi_device *dsi)
{
	struct shift6mq_rm69299 *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id shift6mq_rm69299_of_match[] = {
	{ .compatible = "visionox,rm69299-shift" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, shift6mq_rm69299_of_match);

static struct mipi_dsi_driver shift6mq_rm69299_driver = {
	.probe = shift6mq_rm69299_probe,
	.remove = shift6mq_rm69299_remove,
	.driver = {
		.name = "panel-shift6mq-rm69299",
		.of_match_table = shift6mq_rm69299_of_match,
	},
};
module_mipi_dsi_driver(shift6mq_rm69299_driver);

MODULE_DESCRIPTION("DRM driver for SHIFT6mq RM69299 1080p panel");
MODULE_LICENSE("GPL");
