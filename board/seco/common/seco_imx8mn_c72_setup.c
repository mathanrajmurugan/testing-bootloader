/*
 * 
 *
 * Reading C72 Board type
 *
 * marco.sandrelli@seco.com
 *
 *
 *
 */

#include <common.h>
#include <malloc.h>
#include <errno.h>
#include <asm/io.h>
#include <miiphy.h>
#include <netdev.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm-generic/gpio.h>
#include <fsl_esdhc.h>
#include <mmc.h>
#include <asm/arch/imx8mm_pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/mach-imx/gpio.h>
#include <seco/seco_imx8mm_c72_setup.h>

#define PULLUP_PAD_CTRL  (PAD_CTL_PUE )

/* ____________________________________________________________________________
  |                                                                            |
  |                                  C72 REVISION                              |
  |____________________________________________________________________________|
*/


#define C72_IOMUX_REG(x)        ((x))
#define C72_PADCTRL_REG(x)      ((x))
#define C72_GDIR_REG_IN(x,n)    writel((readl(x + 0x4)) & ~(1<<n), x + 0x4 )
#define C72_PSR_REG(x,n)	(readl(x + 0x8) & (1<<n))

#define shift_0			0
#define shift_1			1
#define shift_2			2
#define shift_3			3

#define GPIO4_PAD_BASE		0x30230000		
/* RAM straps */
#define GPIO_CFG_0		0
#define GPIO_CFG_1              1
/* HDMI straps */
#define GPIO_CFG_2              17
/* Wilink Strap */
#define GPIO_CFG_3		13

#define GPIO1_PAD_BASE          0x30200000
#define GPIO4_PAD_BASE          0x30230000
#define GPIO_CFG_4              15
#define GPIO_CFG_5              22
#define GPIO_CFG_6              21
#define GPIO_CFG_7              0

/* Quad - Quad Lite Strap */
#define GPIO_CFG_8              5
/* SPI - CAN RTC Strap */
#define GPIO_CFG_9              29

struct sizes {
	u32 s0;
	u32 s1;
};

DECLARE_GLOBAL_DATA_PTR;

iomux_v3_cfg_t const board_conf_pads[] = {

        /* RAM CONFIG */
        //IMX8MN_PAD_SAI1_RXFS__GPIO4_IO0	| MUX_PAD_CTRL(PULLUP_PAD_CTRL),   /* cfg_0 */
        //IMX8MN_PAD_SAI1_RXC__GPIO4_IO1	| MUX_PAD_CTRL(PULLUP_PAD_CTRL),   /* cfg_1 */

};


int c72_get_board_configuration ( void ) {

        ulong value = 0;

	/* 
         *
         * CFG code is composed in this way:
         * cfg_0 -> first bit   X 
         * cfg_1 -> second bit  X
         * cfg_2 -> third bit   X
         *  
         */
	
	imx_iomux_v3_setup_multiple_pads(board_conf_pads, ARRAY_SIZE(board_conf_pads));

	/* Mux as Input */
	C72_GDIR_REG_IN(GPIO4_PAD_BASE,GPIO_CFG_0);
	C72_GDIR_REG_IN(GPIO4_PAD_BASE,GPIO_CFG_1);

	/* Read Conf value */
	value = (C72_PSR_REG(GPIO4_PAD_BASE,GPIO_CFG_0) >> GPIO_CFG_0) << shift_0 | 
		(C72_PSR_REG(GPIO4_PAD_BASE,GPIO_CFG_1) >> GPIO_CFG_1) << shift_1 ; 

        return value;

}

