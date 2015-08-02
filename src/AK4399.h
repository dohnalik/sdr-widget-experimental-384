/*
 *  AK4399.h
 *
 *  Created: 25. 1. 2014
 *  Author: Jaroslav Dohnal, Bluestring
 *
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */ 

#ifndef AK4399_H_
#define AK4399_H_

/************************************************************************/
/*				            	INCLUDES                                */
/************************************************************************/

#include "gpio.h"
#include "board.h"
#include "compiler.h"
#include "FreeRTOS.h"
#include "task.h"
#include "device_audio_task.h"
#include "flashc.h"


/************************************************************************/
/*				            	DEFINES                                 */
/************************************************************************/

//address for user page in flash memory for 1 byte volume save
#define USER_PAGE_ADDRESS 0x80800000

#define SPI_CS_PIN AVR32_PIN_PX21
#define SPI_SCK_PIN AVR32_PIN_PX55
#define SPI_SDO_PIN AVR32_PIN_PX56
#define SPI_delay 0x000FFF

#define AK_PD AVR32_PIN_PA23
#define OSC_N441_P48 AVR32_PIN_PA08

#define LED441 AVR32_PIN_PX20
#define LED48  AVR32_PIN_PX22
#define LED882 AVR32_PIN_PX41
#define LED96  AVR32_PIN_PX45
#define LED176 AVR32_PIN_PX42
#define LED192 AVR32_PIN_PX14

/*
#define ROT_INT AVR32_PIN_PA20
#define ROT_DIR AVR32_PIN_PX46*/

//digital filter type
#define SHORT_DELAY   1
#define SHARP_ROLLOFF 0

/************************************************************************/
/*				            	DECLARATIONS                            */
/************************************************************************/

void AK4399_init(U8 digitalFilter);
void sampleRateChanged(U32 sampleFreq);
void AK4399_volume(U8 vol);

void AK4399_write(U8 addr, U8 data);
void spi_write(U16 data);

#endif /* AK4399_H_ */