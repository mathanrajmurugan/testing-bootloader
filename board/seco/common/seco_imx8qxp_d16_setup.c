/*
 * 
 *
 * Reading D16 Board type
 *
 * marco.sandrelli@seco.com
 *
 *
 *
 */

#include <common.h>
#include <errno.h>

#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/clock.h>
#include <asm/arch/sci/sci.h>
#include <asm/arch/iomux.h>
#include <asm/arch/imx8-pins.h>
#include <fsl_esdhc.h>
#include <mmc.h>
#include <asm/arch/sys_proto.h>
#include <seco/seco_imx8qxp_d16_setup.h>


/* ____________________________________________________________________________
  |                                                                            |
  |                                  D16 REVISION                              |
  |____________________________________________________________________________|
*/


int d16_get_board_configuration ( void ) {

        return 0;

}
