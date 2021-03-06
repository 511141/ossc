//
// Copyright (C) 2015-2016  Markus Hiienkari <mhiienka@niksula.hut.fi>
//
// This file is part of Open Source Scan Converter project.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <string.h>
#include "system.h"
#include "avconfig.h"
#include "av_controller.h"
#include "altera_avalon_pio_regs.h"
#include "tvp7002.h"

#define DEFAULT_PRE_COAST       1
#define DEFAULT_POST_COAST      0
#define DEFAULT_SAMPLER_PHASE   16
#define DEFAULT_SYNC_VTH        11
#define DEFAULT_FINE_GAIN       26
#define DEFAULT_FINE_OFFSET     0x80

extern mode_data_t video_modes[], video_modes_def[];
extern alt_u8 video_mode_cnt;
extern alt_u8 update_cur_vm;

// Target configuration
avconfig_t tc;

// Default configuration
const avconfig_t tc_default = {
    .sampler_phase = DEFAULT_SAMPLER_PHASE,
    .sync_vth = DEFAULT_SYNC_VTH,
    .linelen_tol = DEFAULT_LINELEN_TOL,
    .vsync_thold = DEFAULT_VSYNC_THOLD,
    .pre_coast = DEFAULT_PRE_COAST,
    .post_coast = DEFAULT_POST_COAST,
    .col = {
        .r_f_gain = DEFAULT_FINE_GAIN,
        .g_f_gain = DEFAULT_FINE_GAIN,
        .b_f_gain = DEFAULT_FINE_GAIN,
        .r_f_off = DEFAULT_FINE_OFFSET,
        .g_f_off = DEFAULT_FINE_OFFSET,
        .b_f_off = DEFAULT_FINE_OFFSET,
    },
};

int set_default_avconfig()
{
    memcpy(&tc, &tc_default, sizeof(avconfig_t));
    tc.tx_mode = !!(IORD_ALTERA_AVALON_PIO_DATA(PIO_1_BASE) & HDMITX_MODE_MASK);

    memcpy(video_modes, video_modes_def, video_mode_cnt*sizeof(mode_data_t));
    update_cur_vm = 1;

    return 0;
}
