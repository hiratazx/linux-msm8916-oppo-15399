// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2025 The yukiprjkt orgs
// Copyright (c) 2013, The Linux Foundation. All rights reserved. (FIXME)

#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/mod_devicetable.h>
#include <linux/module.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

struct oppo15399tm_nt35521s {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline
struct oppo15399tm_nt35521s *to_oppo15399tm_nt35521s(struct drm_panel *panel)
{
	return container_of(panel, struct oppo15399tm_nt35521s, panel);
}

static void oppo15399tm_nt35521s_reset(struct oppo15399tm_nt35521s *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(15000, 16000);
}

static int oppo15399tm_nt35521s_on(struct oppo15399tm_nt35521s *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xaa, 0x55, 0x25, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x16);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf7, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xff, 0xaa, 0x55, 0x25, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xec, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb, 0xaa, 0xaa);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbc, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc8, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x0f, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1, 0x0f, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbc, 0x78, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x78, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xca, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5, 0x03, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x1e, 0x1e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x0f, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9, 0x34, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba, 0x15, 0x15);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xee, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0,
				     0x00, 0x00, 0x00, 0x16, 0x00, 0x3a, 0x00,
				     0x56, 0x00, 0x6d, 0x00, 0x94, 0x00, 0xb3,
				     0x00, 0xe6);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1,
				     0x01, 0x0f, 0x01, 0x4f, 0x01, 0x82, 0x01,
				     0xd5, 0x02, 0x1a, 0x02, 0x1c, 0x02, 0x5d,
				     0x02, 0xa2);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2,
				     0x02, 0xcb, 0x03, 0x00, 0x03, 0x22, 0x03,
				     0x50, 0x03, 0x6d, 0x03, 0x92, 0x03, 0xab,
				     0x03, 0xc1);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x03, 0xd1, 0x03, 0xd3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
				     0x00, 0x9f, 0x00, 0xa7, 0x00, 0xb5, 0x00,
				     0xc2, 0x00, 0xce, 0x00, 0xe4, 0x00, 0xf9,
				     0x01, 0x22);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5,
				     0x01, 0x42, 0x01, 0x72, 0x01, 0x9d, 0x01,
				     0xe9, 0x02, 0x26, 0x02, 0x28, 0x02, 0x65,
				     0x02, 0xa8);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x02, 0xd0, 0x03, 0x03, 0x03, 0x26, 0x03,
				     0x50, 0x03, 0x6d, 0x03, 0x91, 0x03, 0xa8,
				     0x03, 0xbf);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7, 0x03, 0xd0, 0x03, 0xd3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8,
				     0x00, 0x5c, 0x00, 0x66, 0x00, 0x78, 0x00,
				     0x88, 0x00, 0x97, 0x00, 0xb2, 0x00, 0xcb,
				     0x00, 0xfb);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9,
				     0x01, 0x20, 0x01, 0x57, 0x01, 0x87, 0x01,
				     0xdb, 0x02, 0x1c, 0x02, 0x1e, 0x02, 0x5e,
				     0x02, 0xa4);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba,
				     0x02, 0xcd, 0x03, 0x01, 0x03, 0x26, 0x03,
				     0x5a, 0x03, 0x83, 0x03, 0xa9, 0x03, 0xb0,
				     0x03, 0xbf);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb, 0x03, 0xd1, 0x03, 0xd3);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x08, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1, 0x31, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2, 0x34, 0x2e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x2d, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x00, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5, 0x34, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6, 0x10, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7, 0x34, 0x18);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8, 0x16, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9, 0x34, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba, 0x34, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb, 0x34, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbc, 0x19, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd, 0x34, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbe, 0x13, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbf, 0x03, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x34, 0x2d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1, 0x2e, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2, 0x34, 0x31);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x34, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe5, 0x34, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc4, 0x09, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc5, 0x31, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc6, 0x34, 0x2d);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc7, 0x2e, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc8, 0x03, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc9, 0x34, 0x17);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xca, 0x19, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcb, 0x34, 0x11);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcc, 0x13, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcd, 0x34, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xce, 0x34, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcf, 0x34, 0x12);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd0, 0x10, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd1, 0x34, 0x18);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd2, 0x16, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3, 0x00, 0x02);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd4, 0x34, 0x2e);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd5, 0x2d, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd6, 0x34, 0x31);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd7, 0x34, 0x08);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe6, 0x34, 0x34);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd8,
				     0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd9,
				     0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe7, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xed, 0x30);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1, 0x20, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x20, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe5, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb0, 0x17, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd,
				     0x03, 0x03, 0x01, 0x00, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb1, 0x17, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9, 0x00, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2, 0x17, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3, 0x17, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4, 0x17, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5, 0x17, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6, 0x17, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7, 0x17, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbc, 0x00, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe5, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe6, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe7, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe8, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xe9, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xea, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xeb, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xec, 0x06);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc0, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc1, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc2, 0x0b);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x09);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb2,
				     0x05, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb3,
				     0x05, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb4,
				     0x05, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb5,
				     0x05, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc4, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc5, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc6, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc7, 0x0f);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb6,
				     0x05, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb7,
				     0x05, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb8,
				     0x05, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xb9,
				     0x05, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc8, 0x07, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc9, 0x03, 0x20);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xca, 0x07, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcb, 0x03, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xba,
				     0x53, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbb,
				     0x53, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbc,
				     0x53, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xbd,
				     0x53, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd1,
				     0x00, 0x05, 0x00, 0x07, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd2,
				     0x00, 0x05, 0x04, 0x07, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd3,
				     0x00, 0x00, 0x0a, 0x07, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd4,
				     0x00, 0x00, 0x0a, 0x07, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x05);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd0,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd5,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd6,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd7,
				     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				     0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd8,
				     0x00, 0x00, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x03);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc4, 0x60);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc5, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc6, 0x60);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc7, 0x40);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0x6f, 0x01);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf9, 0x46);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x04);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc3, 0x83);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xc8, 0x80);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd9, 0x01, 0x01, 0x4d);
	mipi_dsi_dcs_set_display_brightness_multi(&dsi_ctx, 0x00ff);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_CONTROL_DISPLAY,
				     0x24);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, MIPI_DCS_WRITE_POWER_SAVE, 0x81);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xf0,
				     0x55, 0xaa, 0x52, 0x08, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xcc,
				     0x40, 0x36, 0x87, 0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xce,
				     0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
				     0x10, 0x10, 0x10, 0x10, 0x10);
	mipi_dsi_dcs_write_seq_multi(&dsi_ctx, 0xd1,
				     0x00, 0x02, 0x03, 0x04, 0x06, 0x08, 0x0a,
				     0x0c, 0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x04,
				     0x02, 0x00);
	mipi_dsi_dcs_exit_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);
	mipi_dsi_dcs_set_display_on_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 20);

	return dsi_ctx.accum_err;
}

static int oppo15399tm_nt35521s_off(struct oppo15399tm_nt35521s *ctx)
{
	struct mipi_dsi_multi_context dsi_ctx = { .dsi = ctx->dsi };

	ctx->dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	mipi_dsi_dcs_set_display_off_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 50);
	mipi_dsi_dcs_enter_sleep_mode_multi(&dsi_ctx);
	mipi_dsi_msleep(&dsi_ctx, 120);

	return dsi_ctx.accum_err;
}

static int oppo15399tm_nt35521s_prepare(struct drm_panel *panel)
{
	struct oppo15399tm_nt35521s *ctx = to_oppo15399tm_nt35521s(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	oppo15399tm_nt35521s_reset(ctx);

	ret = oppo15399tm_nt35521s_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int oppo15399tm_nt35521s_unprepare(struct drm_panel *panel)
{
	struct oppo15399tm_nt35521s *ctx = to_oppo15399tm_nt35521s(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = oppo15399tm_nt35521s_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode oppo15399tm_nt35521s_mode = {
	.clock = (720 + 240 + 8 + 230) * (1280 + 26 + 8 + 26) * 60 / 1000,
	.hdisplay = 720,
	.hsync_start = 720 + 240,
	.hsync_end = 720 + 240 + 8,
	.htotal = 720 + 240 + 8 + 230,
	.vdisplay = 1280,
	.vsync_start = 1280 + 26,
	.vsync_end = 1280 + 26 + 8,
	.vtotal = 1280 + 26 + 8 + 26,
	.width_mm = 62,
	.height_mm = 110,
	.type = DRM_MODE_TYPE_DRIVER,
};

static int oppo15399tm_nt35521s_get_modes(struct drm_panel *panel,
					  struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &oppo15399tm_nt35521s_mode);
}

static const struct drm_panel_funcs oppo15399tm_nt35521s_panel_funcs = {
	.prepare = oppo15399tm_nt35521s_prepare,
	.unprepare = oppo15399tm_nt35521s_unprepare,
	.get_modes = oppo15399tm_nt35521s_get_modes,
};

static int oppo15399tm_nt35521s_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct oppo15399tm_nt35521s *ctx;
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

	dsi->lanes = 3;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO | MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_MODE_VIDEO_HSE |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS |
			  MIPI_DSI_MODE_VIDEO_NO_HFP |
			  MIPI_DSI_MODE_VIDEO_NO_HBP |
			  MIPI_DSI_MODE_VIDEO_NO_HSA;

	drm_panel_init(&ctx->panel, dev, &oppo15399tm_nt35521s_panel_funcs,
		       DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	ret = drm_panel_of_backlight(&ctx->panel);
	if (ret)
		return dev_err_probe(dev, ret, "Failed to get backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void oppo15399tm_nt35521s_remove(struct mipi_dsi_device *dsi)
{
	struct oppo15399tm_nt35521s *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id oppo15399tm_nt35521s_of_match[] = {
	{ .compatible = "mdss,oppo15399tm-nt35521s" }, // FIXME
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, oppo15399tm_nt35521s_of_match);

static struct mipi_dsi_driver oppo15399tm_nt35521s_driver = {
	.probe = oppo15399tm_nt35521s_probe,
	.remove = oppo15399tm_nt35521s_remove,
	.driver = {
		.name = "panel-oppo15399tm-nt35521s",
		.of_match_table = oppo15399tm_nt35521s_of_match,
	},
};
module_mipi_dsi_driver(oppo15399tm_nt35521s_driver);

MODULE_AUTHOR("ItzKaguya <itzkaguya@yukiprjkt.my.id>"); // FIXME
MODULE_DESCRIPTION("DRM driver for oppo15399tm nt35521s 720p video mode dsi panel");
MODULE_LICENSE("GPL");
