// SPDX-License-Identifier: GPL-2.0-only
/* Copyright (c) 2022 Nia Espera <a5b6@riseup.net>
 * Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
 * Copyright (c) 2022, The Linux Foundation. All rights reserved.
 */

#define DEBUG

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/regulator/consumer.h>
#include <linux/swab.h>
#include <linux/backlight.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>

struct samsung_s6e3fc2x01 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	bool first_prepare;
	struct regulator_bulk_data supplies[3];
	struct gpio_desc *reset_gpio;
};

static inline
struct samsung_s6e3fc2x01 *to_samsung_s6e3fc2x01(struct drm_panel *panel)
{
	return container_of(panel, struct samsung_s6e3fc2x01, panel);
}

static void samsung_s6e3fc2x01_reset(struct samsung_s6e3fc2x01 *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(2000, 3000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int samsung_s6e3fc2x01_on(struct samsung_s6e3fc2x01 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq(dsi, 0x9f, 0xa5, 0xa5);

	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	usleep_range(10000, 11000);

	mipi_dsi_dcs_write_seq(dsi, 0x9f, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xcd, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5);
	usleep_range(15000, 16000);
	mipi_dsi_dcs_write_seq(dsi, 0x9f, 0xa5, 0xa5);

	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	if (ret < 0) {
		dev_err(dev, "Failed to set tear on: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0x9f, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xeb, 0x17, 0x41, 0x92, 0x0e, 0x10, 0x82, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5);

	ret = mipi_dsi_dcs_set_column_address(dsi, 0x0000, 0x0437);
	if (ret < 0) {
		dev_err(dev, "Failed to set column address: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_dcs_set_page_address(dsi, 0x0000, 0x0923);
	if (ret < 0) {
		dev_err(dev, "Failed to set page address: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x09);
	mipi_dsi_dcs_write_seq(dsi, 0xe8, 0x10, 0x30);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x07);
	mipi_dsi_dcs_write_seq(dsi, 0xb7, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x08);
	mipi_dsi_dcs_write_seq(dsi, 0xb7, 0x12);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5);
	mipi_dsi_dcs_write_seq(dsi, 0xfc, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xe3, 0x88);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x07);
	mipi_dsi_dcs_write_seq(dsi, 0xed, 0x67);
	mipi_dsi_dcs_write_seq(dsi, 0xfc, 0xa5, 0xa5);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x20);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_POWER_SAVE, 0x00);
	usleep_range(1000, 2000);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xb3, 0x00, 0xc1);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}

	usleep_range(10000, 11000);
	mipi_dsi_dcs_write_seq(dsi, 0x9f, 0xa5, 0xa5);
	mipi_dsi_dcs_write_seq(dsi, 0x29);
	mipi_dsi_dcs_write_seq(dsi, 0x9f, 0x5a, 0x5a);

	return 0;
}

static int samsung_s6e3fc2x01_off(struct samsung_s6e3fc2x01 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq(dsi, 0x9f, 0xa5, 0xa5);

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(&dsi->dev, "Failed to set display off: %d\n", ret);
		return ret;
	}
	usleep_range(10000, 11000);

	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a);
	usleep_range(16000, 17000);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x50);
	mipi_dsi_dcs_write_seq(dsi, 0xb9, 0x82);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5);
	usleep_range(16000, 17000);
	msleep(40);

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(&dsi->dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0x9f, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x05);
	mipi_dsi_dcs_write_seq(dsi, 0xf4, 0x01);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5);
	msleep(160);

	return 0;
}

static int samsung_s6e3fc2x01_prepare(struct drm_panel *panel)
{
	struct samsung_s6e3fc2x01 *ctx = to_samsung_s6e3fc2x01(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	dev_dbg(dev, "%s\n", __func__);

	/*
	 * On boot the panel has already been initialised, if the regulators are
	 * already enabled then we can safely assume that the panel is on and we
	 * can skip the prepare.
	 */
	if (regulator_is_enabled(ctx->supplies[0].consumer) && ctx->first_prepare) {
		ctx->first_prepare = false;
		dev_dbg(dev, "First prepare!\n");
		return 0;
	}

	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret < 0) {
		dev_err(dev, "Failed to enable regulator: %d\n", ret);
		return ret;
	}

	samsung_s6e3fc2x01_reset(ctx);

	ret = samsung_s6e3fc2x01_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
		return ret;
	}

	return 0;
}

static int samsung_s6e3fc2x01_disable(struct drm_panel *panel)
{
	struct samsung_s6e3fc2x01 *ctx = to_samsung_s6e3fc2x01(panel);

	dev_dbg(&ctx->dsi->dev, "%s\n", __func__);
	
	samsung_s6e3fc2x01_off(ctx);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	regulator_bulk_disable(ARRAY_SIZE(ctx->supplies), ctx->supplies);

	return 0;
}

static const struct drm_display_mode samsung_s6e3fc2x01_mode = {
	.clock = (1080 + 72 + 16 + 36) * (2340 + 32 + 4 + 18) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 72,
	.hsync_end = 1080 + 72 + 16,
	.htotal = 1080 + 72 + 16 + 36,
	.vdisplay = 2340,
	.vsync_start = 2340 + 32,
	.vsync_end = 2340 + 32 + 4,
	.vtotal = 2340 + 32 + 4 + 18,
	.width_mm = 68,
	.height_mm = 145,
};

static int samsung_s6e3fc2x01_get_modes(struct drm_panel *panel,
					struct drm_connector *connector)
{
	struct drm_display_mode *mode;

	mode = drm_mode_duplicate(connector->dev, &samsung_s6e3fc2x01_mode);
	if (!mode)
		return -ENOMEM;

	drm_mode_set_name(mode);

	mode->type = DRM_MODE_TYPE_DRIVER | DRM_MODE_TYPE_PREFERRED;
	connector->display_info.width_mm = mode->width_mm;
	connector->display_info.height_mm = mode->height_mm;
	drm_mode_probed_add(connector, mode);

	return 1;
}

static const struct drm_panel_funcs samsung_s6e3fc2x01_panel_funcs = {
	.prepare = samsung_s6e3fc2x01_prepare,
	.disable = samsung_s6e3fc2x01_disable,
	.get_modes = samsung_s6e3fc2x01_get_modes,
};

static int s6e3fc2x01_panel_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	int err;
	u16 brightness;

	brightness = (u16)backlight_get_brightness(bl);
	// This panel needs the high and low bytes swapped for the brightness value
	brightness = __swab16(brightness);

	err = mipi_dsi_dcs_set_display_brightness(dsi, brightness);
	if (err < 0)
		return err;

	return 0;
}

static const struct backlight_ops s6e3fc2x01_panel_bl_ops = {
	.update_status = s6e3fc2x01_panel_bl_update_status,
};

static struct backlight_device *
s6e3fc2x01_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_PLATFORM,
		.brightness = 1023,
		.max_brightness = 1023,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
					      &s6e3fc2x01_panel_bl_ops, &props);
}

static int samsung_s6e3fc2x01_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct samsung_s6e3fc2x01 *ctx;
	int ret;

	pr_info("samsung_s6e3fc2x01_probe\n");

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->supplies[0].supply = "vddio";
	ctx->supplies[1].supply = "vci";
	ctx->supplies[2].supply = "poc";

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret)
		return dev_err_probe(dev, ret,
				     "Failed to get vddio regulator\n");

	/* Regulators are all boot-on, enable them to balance the refcounts so we can disable
	 * them later in the first prepare() call */
	ret = regulator_bulk_enable(ARRAY_SIZE(ctx->supplies), ctx->supplies);
	if (ret < 0)
		return dev_err_probe(dev, ret,
				     "Failed to enable regulators\n");

	ctx->first_prepare = true;
	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
				     "Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;

	drm_panel_init(&ctx->panel, dev, &samsung_s6e3fc2x01_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);

	ctx->panel.backlight = s6e3fc2x01_create_backlight(dsi);
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

static void samsung_s6e3fc2x01_remove(struct mipi_dsi_device *dsi)
{
	struct samsung_s6e3fc2x01 *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);

	return;
}

static const struct of_device_id samsung_s6e3fc2x01_of_match[] = {
	{
		.compatible = "samsung,s6e3fc2x01",
		.data = &samsung_s6e3fc2x01_mode,
	},
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, samsung_s6e3fc2x01_of_match);

static struct mipi_dsi_driver samsung_s6e3fc2x01_driver = {
	.probe = samsung_s6e3fc2x01_probe,
	.remove = samsung_s6e3fc2x01_remove,
	.driver = {
		.name = "panel-samsung-s6e3fc2x01",
		.of_match_table = samsung_s6e3fc2x01_of_match,
	},
};
module_mipi_dsi_driver(samsung_s6e3fc2x01_driver);

MODULE_AUTHOR("Nia Espera <a5b6@riseup.net>");
MODULE_DESCRIPTION("DRM driver for OnePlus 6T Panel");
MODULE_LICENSE("GPL v2");
