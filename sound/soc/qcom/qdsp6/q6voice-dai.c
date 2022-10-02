// SPDX-License-Identifier: GPL-2.0
// Copyright (c) 2012-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2020, Stephan Gerhold

#include <linux/module.h>
#include <linux/platform_device.h>
#include <sound/soc.h>
#include <dt-bindings/sound/qcom,q6afe.h>
#include <dt-bindings/sound/qcom,q6voice.h>
#include "q6afe.h"
#include "q6voice.h"

#define DRV_NAME	"q6voice-dai"

static int q6voice_dai_startup(struct snd_pcm_substream *substream,
			       struct snd_soc_dai *dai)
{
	struct q6voice *v = snd_soc_dai_get_drvdata(dai);
	struct device *dev = dai->component->dev;
	int ret;

	switch (dai->driver->id) {
	case CS_VOICE:
		ret = q6voice_start(v, Q6VOICE_PATH_VOICE, substream->stream);
		break;
	case VOICEMMODE1:
		ret = q6voice_start(v, Q6VOICE_PATH_VOICEMMODE1, substream->stream);
		break;
	default:
		dev_err(dev, "Invalid dai id %x\n", dai->driver->id);
		ret = -EINVAL;
	}

	return ret;
}

static void q6voice_dai_shutdown(struct snd_pcm_substream *substream,
				 struct snd_soc_dai *dai)
{
	struct q6voice *v = snd_soc_dai_get_drvdata(dai);
	struct device *dev = dai->component->dev;

	switch (dai->driver->id) {
	case CS_VOICE:
		q6voice_stop(v, Q6VOICE_PATH_VOICE, substream->stream);
		break;
	case VOICEMMODE1:
		q6voice_stop(v, Q6VOICE_PATH_VOICEMMODE1, substream->stream);
		break;
	default:
		dev_err(dev, "Invalid dai id %x\n", dai->driver->id);
	}
}

static struct snd_soc_dai_ops q6voice_dai_ops = {
	.startup = q6voice_dai_startup,
	.shutdown = q6voice_dai_shutdown,
};

static struct snd_soc_dai_driver q6voice_dais[] = {
	{
		.id = CS_VOICE,
		.name = "CS-VOICE",
		/* The constraints here are not really meaningful... */
		.playback = {
			.stream_name =	"CS-VOICE Playback",
			.formats =	SNDRV_PCM_FMTBIT_S16_LE,
			.rates =	SNDRV_PCM_RATE_8000,
			.rate_min =	8000,
			.rate_max =	8000,
			.channels_min =	1,
			.channels_max =	1,
		},
		.capture = {
			.stream_name =	"CS-VOICE Capture",
			.formats =	SNDRV_PCM_FMTBIT_S16_LE,
			.rates =	SNDRV_PCM_RATE_8000,
			.rate_min =	8000,
			.rate_max =	8000,
			.channels_min =	1,
			.channels_max =	1,
		},
		.ops = &q6voice_dai_ops,
	},
	{
		.id = VOICEMMODE1,
		.name = "VoiceMMode1",
		/* The constraints here are not really meaningful... */
		.playback = {
			.stream_name = "VoiceMMode1 Playback",
			.formats = SNDRV_PCM_FMTBIT_S16_LE,
			.rates =   SNDRV_PCM_RATE_8000,
			.rate_min = 8000,
			.rate_max = 8000,
			.channels_min = 1,
			.channels_max = 1,
	    },
		.capture = {
			.stream_name = "VoiceMMode1 Capture",
			.formats = SNDRV_PCM_FMTBIT_S16_LE,
			.rates =   SNDRV_PCM_RATE_8000,
			.rate_min = 8000,
			.rate_max = 8000,
			.channels_min = 1,
			.channels_max = 1,
		},
		.ops = &q6voice_dai_ops,
	},
};

/* FIXME: Use codec2codec instead */
static struct snd_pcm_hardware q6voice_dai_hardware = {
	.info =			SNDRV_PCM_INFO_INTERLEAVED,
	.buffer_bytes_max =	4096 * 2,
	.period_bytes_min =	2048,
	.period_bytes_max =	4096,
	.periods_min =		2,
	.periods_max =		4,
	.fifo_size =		0,
};

static int q6voice_dai_open(struct snd_soc_component *component,
			    struct snd_pcm_substream *substream)
{
	substream->runtime->hw = q6voice_dai_hardware;
	return 0;
}

static int q6voice_get_mixer(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	struct snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct q6voice *v = snd_soc_component_get_drvdata(c);

	switch (mc->reg) {
	case PRIMARY_MI2S_TX:
	case SECONDARY_MI2S_TX:
	case TERTIARY_MI2S_TX:
	case QUATERNARY_MI2S_TX:
	case QUINARY_MI2S_TX:
	case SLIMBUS_0_TX:
	case SLIMBUS_1_TX:
	case SLIMBUS_2_TX:
	case SLIMBUS_3_TX:
	case SLIMBUS_4_TX:
	case SLIMBUS_5_TX:
	case SLIMBUS_6_TX:
		if (q6voice_get_port(v, Q6VOICE_PORT_TX) == mc->reg)
			ucontrol->value.integer.value[0] = 1;
		else
			ucontrol->value.integer.value[0] = 0;
		break;
	case PRIMARY_MI2S_RX:
	case SECONDARY_MI2S_RX:
	case TERTIARY_MI2S_RX:
	case QUATERNARY_MI2S_RX:
	case QUINARY_MI2S_RX:
	case SLIMBUS_0_RX:
	case SLIMBUS_1_RX:
	case SLIMBUS_2_RX:
	case SLIMBUS_3_RX:
	case SLIMBUS_4_RX:
	case SLIMBUS_5_RX:
	case SLIMBUS_6_RX:
		if (q6voice_get_port(v, Q6VOICE_PORT_RX) == mc->reg)
			ucontrol->value.integer.value[0] = 1;
		else
			ucontrol->value.integer.value[0] = 0;
		break;
	default:
		dev_err(c->dev, "%s: invalid mixer request: %d\n", __func__, mc->reg);
	}

	return 0;
}

static int q6voice_put_mixer(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_soc_dapm_context *dapm = snd_soc_dapm_kcontrol_dapm(kcontrol);
	struct snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	struct soc_mixer_control *mc =
		(struct soc_mixer_control *)kcontrol->private_value;
	struct q6voice *v = snd_soc_component_get_drvdata(c);
	struct snd_soc_dapm_update *update = NULL;

	switch (mc->reg) {
	case PRIMARY_MI2S_TX:
	case SECONDARY_MI2S_TX:
	case TERTIARY_MI2S_TX:
	case QUATERNARY_MI2S_TX:
	case QUINARY_MI2S_TX:
	case SLIMBUS_0_TX:
	case SLIMBUS_1_TX:
	case SLIMBUS_2_TX:
	case SLIMBUS_3_TX:
	case SLIMBUS_4_TX:
	case SLIMBUS_5_TX:
	case SLIMBUS_6_TX:
		q6voice_set_port(v, Q6VOICE_PORT_TX, mc->reg);
		break;
	case PRIMARY_MI2S_RX:
	case SECONDARY_MI2S_RX:
	case TERTIARY_MI2S_RX:
	case QUATERNARY_MI2S_RX:
	case QUINARY_MI2S_RX:
	case SLIMBUS_0_RX:
	case SLIMBUS_1_RX:
	case SLIMBUS_2_RX:
	case SLIMBUS_3_RX:
	case SLIMBUS_4_RX:
	case SLIMBUS_5_RX:
	case SLIMBUS_6_RX:
		q6voice_set_port(v, Q6VOICE_PORT_RX, mc->reg);
		break;
	default:
		dev_err(c->dev, "%s: invalid mixer setting: %d\n", __func__, mc->reg);
	}

	if (ucontrol->value.integer.value[0])
		snd_soc_dapm_mixer_update_power(dapm, kcontrol, 1, update);
	else
		snd_soc_dapm_mixer_update_power(dapm, kcontrol, 0, update);

	return 1;
}

static const struct snd_kcontrol_new cs_voice_tx_mixer_controls[] = {
	SOC_SINGLE_EXT("PRI_MI2S_TX", PRIMARY_MI2S_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SEC_MI2S_TX", SECONDARY_MI2S_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("TERT_MI2S_TX", TERTIARY_MI2S_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("QUAT_MI2S_TX", QUATERNARY_MI2S_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("QUIN_MI2S_TX", QUINARY_MI2S_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_0_TX", SLIMBUS_0_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_1_TX", SLIMBUS_1_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_2_TX", SLIMBUS_2_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_3_TX", SLIMBUS_3_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_4_TX", SLIMBUS_4_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_5_TX", SLIMBUS_5_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_6_TX", SLIMBUS_6_TX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
};

static const struct snd_kcontrol_new voicemmode1_tx_mixer_controls[] = {
	SOC_SINGLE_EXT("PRI_MI2S_TX", PRIMARY_MI2S_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SEC_MI2S_TX", SECONDARY_MI2S_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("TERT_MI2S_TX", TERTIARY_MI2S_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("QUAT_MI2S_TX", QUATERNARY_MI2S_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("QUIN_MI2S_TX", QUINARY_MI2S_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_0_TX", SLIMBUS_0_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_1_TX", SLIMBUS_1_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_2_TX", SLIMBUS_2_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_3_TX", SLIMBUS_3_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_4_TX", SLIMBUS_4_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_5_TX", SLIMBUS_5_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("SLIMBUS_6_TX", SLIMBUS_6_TX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
};

static const struct snd_kcontrol_new primary_mi2s_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", PRIMARY_MI2S_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", PRIMARY_MI2S_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new secondary_mi2s_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", SECONDARY_MI2S_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", SECONDARY_MI2S_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new tertiary_mi2s_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", TERTIARY_MI2S_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", TERTIARY_MI2S_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new quaternary_mi2s_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", QUATERNARY_MI2S_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", QUATERNARY_MI2S_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new quinary_mi2s_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", QUINARY_MI2S_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", QUINARY_MI2S_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new slimbus_0_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", SLIMBUS_0_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", SLIMBUS_0_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new slimbus_1_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", SLIMBUS_1_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", SLIMBUS_1_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new slimbus_2_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", SLIMBUS_2_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", SLIMBUS_2_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new slimbus_3_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", SLIMBUS_3_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", SLIMBUS_3_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new slimbus_4_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", SLIMBUS_4_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", SLIMBUS_4_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new slimbus_5_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", SLIMBUS_5_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", SLIMBUS_5_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_kcontrol_new slimbus_6_rx_mixer_controls[] = {
	SOC_SINGLE_EXT("CS-Voice", SLIMBUS_6_RX, CS_VOICE, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer),
	SOC_SINGLE_EXT("VoiceMMode1", SLIMBUS_6_RX, VOICEMMODE1, 1, 0,
		       q6voice_get_mixer, q6voice_put_mixer)
};

static const struct snd_soc_dapm_widget q6voice_dapm_widgets[] = {
	SND_SOC_DAPM_AIF_IN("CS-VOICE_DL1", "CS-VOICE Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("CS-VOICE_UL1", "CS-VOICE Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_IN("VOICEMMODE1_DL", "VoiceMMode1 Playback", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("VOICEMMODE1_UL", "VoiceMMode1 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_MIXER("CS-Voice Capture Mixer", SND_SOC_NOPM, 0, 0,
			   cs_voice_tx_mixer_controls,
			   ARRAY_SIZE(cs_voice_tx_mixer_controls)),
	SND_SOC_DAPM_MIXER("VoiceMMode1 Capture Mixer", SND_SOC_NOPM, 0, 0,
			   voicemmode1_tx_mixer_controls,
			   ARRAY_SIZE(voicemmode1_tx_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRI_MI2S_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   primary_mi2s_rx_mixer_controls,
			   ARRAY_SIZE(primary_mi2s_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SEC_MI2S_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   secondary_mi2s_rx_mixer_controls,
			   ARRAY_SIZE(secondary_mi2s_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("TERT_MI2S_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   tertiary_mi2s_rx_mixer_controls,
			   ARRAY_SIZE(tertiary_mi2s_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUAT_MI2S_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   quaternary_mi2s_rx_mixer_controls,
			   ARRAY_SIZE(quaternary_mi2s_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUIN_MI2S_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   quinary_mi2s_rx_mixer_controls,
			   ARRAY_SIZE(quinary_mi2s_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_0_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_0_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_0_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_1_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_1_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_1_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_2_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_2_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_2_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_3_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_3_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_3_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_4_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_4_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_4_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_5_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_5_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_5_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_6_RX Voice Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_6_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_6_rx_mixer_controls)),
};

static const struct snd_soc_dapm_route q6voice_dapm_routes[] = {
	{ "CS-Voice Capture Mixer",	"PRI_MI2S_TX",	"PRI_MI2S_TX" },
	{ "CS-Voice Capture Mixer",	"SEC_MI2S_TX",	"SEC_MI2S_TX" },
	{ "CS-Voice Capture Mixer",	"TERT_MI2S_TX",	"TERT_MI2S_TX" },
	{ "CS-Voice Capture Mixer",	"QUAT_MI2S_TX",	"QUAT_MI2S_TX" },
	{ "CS-Voice Capture Mixer",	"QUIN_MI2S_TX",	"QUIN_MI2S_TX" },
	{ "CS-Voice Capture Mixer",	"SLIMBUS_0_TX",	"SLIMBUS_0_TX" },
	{ "CS-Voice Capture Mixer",	"SLIMBUS_1_TX",	"SLIMBUS_1_TX" },
	{ "CS-Voice Capture Mixer",	"SLIMBUS_2_TX",	"SLIMBUS_2_TX" },
	{ "CS-Voice Capture Mixer",	"SLIMBUS_3_TX",	"SLIMBUS_3_TX" },
	{ "CS-Voice Capture Mixer",	"SLIMBUS_4_TX",	"SLIMBUS_4_TX" },
	{ "CS-Voice Capture Mixer",	"SLIMBUS_5_TX",	"SLIMBUS_5_TX" },
	{ "CS-Voice Capture Mixer",	"SLIMBUS_6_TX",	"SLIMBUS_6_TX" },
	{ "CS-VOICE_UL1",		NULL,		"CS-Voice Capture Mixer" },

	{ "PRI_MI2S_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "SEC_MI2S_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "TERT_MI2S_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "QUAT_MI2S_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "QUIN_MI2S_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "SLIMBUS_0_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "SLIMBUS_1_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "SLIMBUS_2_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "SLIMBUS_3_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "SLIMBUS_4_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "SLIMBUS_5_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },
	{ "SLIMBUS_6_RX Voice Mixer",	"CS-Voice",	"CS-VOICE_DL1" },

	{ "VoiceMMode1 Capture Mixer",	"PRI_MI2S_TX",	"PRI_MI2S_TX" },
	{ "VoiceMMode1 Capture Mixer",	"SEC_MI2S_TX",	"SEC_MI2S_TX" },
	{ "VoiceMMode1 Capture Mixer",	"TERT_MI2S_TX",	"TERT_MI2S_TX" },
	{ "VoiceMMode1 Capture Mixer",	"QUAT_MI2S_TX",	"QUAT_MI2S_TX" },
	{ "VoiceMMode1 Capture Mixer",	"QUIN_MI2S_TX",	"QUIN_MI2S_TX" },
	{ "VoiceMMode1 Capture Mixer",	"SLIMBUS_0_TX",	"SLIMBUS_0_TX" },
	{ "VoiceMMode1 Capture Mixer",	"SLIMBUS_1_TX",	"SLIMBUS_1_TX" },
	{ "VoiceMMode1 Capture Mixer",	"SLIMBUS_2_TX",	"SLIMBUS_2_TX" },
	{ "VoiceMMode1 Capture Mixer",	"SLIMBUS_3_TX",	"SLIMBUS_3_TX" },
	{ "VoiceMMode1 Capture Mixer",	"SLIMBUS_4_TX",	"SLIMBUS_4_TX" },
	{ "VoiceMMode1 Capture Mixer",	"SLIMBUS_5_TX",	"SLIMBUS_5_TX" },
	{ "VoiceMMode1 Capture Mixer",	"SLIMBUS_6_TX",	"SLIMBUS_6_TX" },
	{ "VOICEMMODE1_UL",		NULL,		"VoiceMMode1 Capture Mixer" },

	{ "PRI_MI2S_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "SEC_MI2S_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "TERT_MI2S_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "QUAT_MI2S_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "QUIN_MI2S_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "SLIMBUS_0_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "SLIMBUS_1_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "SLIMBUS_2_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "SLIMBUS_3_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "SLIMBUS_4_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "SLIMBUS_5_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },
	{ "SLIMBUS_6_RX Voice Mixer",	"VoiceMMode1",	"VOICEMMODE1_DL" },

	{ "PRI_MI2S_RX",		NULL,		"PRI_MI2S_RX Voice Mixer" },
	{ "SEC_MI2S_RX",		NULL,		"SEC_MI2S_RX Voice Mixer" },
	{ "TERT_MI2S_RX",		NULL,		"TERT_MI2S_RX Voice Mixer" },
	{ "QUAT_MI2S_RX",		NULL,		"QUAT_MI2S_RX Voice Mixer" },
	{ "QUIN_MI2S_RX",		NULL,		"QUIN_MI2S_RX Voice Mixer" },
	{ "SLIMBUS_0_RX",		NULL,		"SLIMBUS_0_RX Voice Mixer" },
	{ "SLIMBUS_1_RX",		NULL,		"SLIMBUS_1_RX Voice Mixer" },
	{ "SLIMBUS_2_RX",		NULL,		"SLIMBUS_2_RX Voice Mixer" },
	{ "SLIMBUS_3_RX",		NULL,		"SLIMBUS_3_RX Voice Mixer" },
	{ "SLIMBUS_4_RX",		NULL,		"SLIMBUS_4_RX Voice Mixer" },
	{ "SLIMBUS_5_RX",		NULL,		"SLIMBUS_5_RX Voice Mixer" },
	{ "SLIMBUS_6_RX",		NULL,		"SLIMBUS_6_RX Voice Mixer" },
};

static unsigned int q6voice_reg_read(struct snd_soc_component *component,
				     unsigned int reg)
{
	/* default value */
	return 0;
}

static int q6voice_reg_write(struct snd_soc_component *component,
			     unsigned int reg, unsigned int val)
{
	/* dummy */
	return 0;
}

static const struct snd_soc_component_driver q6voice_dai_component = {
	.name = DRV_NAME,
	.open = q6voice_dai_open,

	.dapm_widgets = q6voice_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(q6voice_dapm_widgets),
	.dapm_routes = q6voice_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(q6voice_dapm_routes),
	.read = q6voice_reg_read,
	.write = q6voice_reg_write,

	/* Needs to probe after q6afe */
	.probe_order = SND_SOC_COMP_ORDER_LATE,
};

static int q6voice_dai_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct q6voice *v;

	v = q6voice_create(dev);
	if (IS_ERR(v))
		return PTR_ERR(v);

	dev_set_drvdata(dev, v);

	return devm_snd_soc_register_component(dev, &q6voice_dai_component,
					       q6voice_dais,
					       ARRAY_SIZE(q6voice_dais));
}

static const struct of_device_id q6voice_dai_device_id[] = {
	{ .compatible = "qcom,q6voice-dais" },
	{},
};
MODULE_DEVICE_TABLE(of, q6voice_dai_device_id);

static struct platform_driver q6voice_dai_platform_driver = {
	.driver = {
		.name = "q6voice-dai",
		.of_match_table = of_match_ptr(q6voice_dai_device_id),
	},
	.probe = q6voice_dai_probe,
};
module_platform_driver(q6voice_dai_platform_driver);

MODULE_AUTHOR("Stephan Gerhold <stephan@gerhold.net>");
MODULE_DESCRIPTION("Q6Voice DAI driver");
MODULE_LICENSE("GPL v2");
