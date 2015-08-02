/*
 *  AK4399.c
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

/************************************************************************/
/*				            	INCLUDES                                */
/************************************************************************/

#include "AK4399.h"

/************************************************************************/
/*				            	DEFINES                                 */
/************************************************************************/


void delay(U32 delay)
{
	while (delay !=0)
	{
		delay--;
	}
}

void AK4399_init(U8 digitalFilter)
{
	gpio_set_gpio_pin(AK_PD); //power up
	
	AK4399_write(0x00, 0x87); //I2S, !RST
	AK4399_write(0x01, (digitalFilter<<5 | 0x02)); //select digital filter
	
	//encoder_init(); //inits encoder task and stuff in rotary_encoder.h
}

void sampleRateChanged(U32 sampleFreq)
{ //function is externally called from UAC1 and UAC2 USB special request
	switch (sampleFreq)
	{
	case 44100:
	    gpio_clr_gpio_pin(OSC_N441_P48); //oscillator *44.1
		
		gpio_set_gpio_pin(LED441); //44.1
		gpio_clr_gpio_pin(LED48); //48
		gpio_clr_gpio_pin(LED882); //88.2
		gpio_clr_gpio_pin(LED96); //96
		gpio_clr_gpio_pin(LED176); //176.4
		gpio_clr_gpio_pin(LED192); //192
		break;
	case 48000:
	    gpio_set_gpio_pin(OSC_N441_P48); //oscillator *48
		
		gpio_clr_gpio_pin(LED441); //44.1
		gpio_set_gpio_pin(LED48); //48
		gpio_clr_gpio_pin(LED882); //88.2
		gpio_clr_gpio_pin(LED96); //96
		gpio_clr_gpio_pin(LED176); //176.4
		gpio_clr_gpio_pin(LED192); //192
		break;
	case 88200:
	    gpio_clr_gpio_pin(OSC_N441_P48); //oscillator *44.1	
		    
		gpio_clr_gpio_pin(LED441); //44.1
		gpio_clr_gpio_pin(LED48); //48
		gpio_set_gpio_pin(LED882); //88.2
		gpio_clr_gpio_pin(LED96); //96
		gpio_clr_gpio_pin(LED176); //176.4
		gpio_clr_gpio_pin(LED192); //192
		break;
	case 96000:
	    gpio_set_gpio_pin(OSC_N441_P48); //oscillator *48
		
		gpio_clr_gpio_pin(LED441); //44.1
		gpio_clr_gpio_pin(LED48); //48
		gpio_clr_gpio_pin(LED882); //88.2
		gpio_set_gpio_pin(LED96); //96
		gpio_clr_gpio_pin(LED176); //176.4
		gpio_clr_gpio_pin(LED192); //192
		break;
	case 176400:
	    gpio_clr_gpio_pin(OSC_N441_P48); //oscillator *44.1
		
		gpio_clr_gpio_pin(LED441); //44.1
		gpio_clr_gpio_pin(LED48); //48
		gpio_clr_gpio_pin(LED882); //88.2
		gpio_clr_gpio_pin(LED96); //96
		gpio_set_gpio_pin(LED176); //176.4
		gpio_clr_gpio_pin(LED192); //192
		break;
	case 192000:
	    gpio_set_gpio_pin(OSC_N441_P48); //oscillator *48
		
		gpio_clr_gpio_pin(LED441); //44.1
		gpio_clr_gpio_pin(LED48); //48
		gpio_clr_gpio_pin(LED882); //88.2
		gpio_clr_gpio_pin(LED96); //96
		gpio_clr_gpio_pin(LED176); //176.4
		gpio_set_gpio_pin(LED192); //192
		break;
	case 352800:
		gpio_clr_gpio_pin(OSC_N441_P48); //oscillator *44.1
			
		gpio_clr_gpio_pin(LED441); //44.1
		gpio_clr_gpio_pin(LED48); //48
		gpio_clr_gpio_pin(LED882); //88.2
		gpio_clr_gpio_pin(LED96); //96
		gpio_set_gpio_pin(LED176); //176.4
		gpio_clr_gpio_pin(LED192); //192
		break;
	case 384000:
		gpio_set_gpio_pin(OSC_N441_P48); //oscillator *48
			
		gpio_clr_gpio_pin(LED441); //44.1
		gpio_clr_gpio_pin(LED48); //48
		gpio_clr_gpio_pin(LED882); //88.2
		gpio_clr_gpio_pin(LED96); //96
		gpio_clr_gpio_pin(LED176); //176.4
		gpio_set_gpio_pin(LED192); //192
		break;
	}
}

void AK4399_volume(U8 vol)
{ //write 8bit volume into AK volume registers

	AK4399_write(0x03, vol);
	AK4399_write(0x04, vol);
}

void AK4399_write(U8 addr, U8 data)
{
	U16 i;
	i = (1<<5) | addr;
	spi_write((i<<8) | data);
}

/*
void volSave(U8 volume){
	// The flash data lives in FLASH_content array during normal operations.
	// The content of the array is read from FLASH user page to memory by FLASH_read_page() and
	// stored to user page by FLASH_store_page()

	static U8 FLASH_content[FLASH_SIZE];

	void FLASH_store_page(void)
	{
		flashc_memcpy((void *)USER_PAGE_ADDRESS, &FLASH_content, sizeof(FLASH_content), TRUE);
	}

	void FLASH_read_page(void)
	{
		memcpy(&FLASH_content, (void *)USER_PAGE_ADDRESS, sizeof(FLASH_content));
	}
*/

void spi_write(U16 data){
	
	int i;
		
	gpio_clr_gpio_pin(SPI_CS_PIN); //CS low
	delay(SPI_delay);
	for (i=15; i>=0; i--)
	{
		gpio_clr_gpio_pin(SPI_SCK_PIN); //SCK low
		delay(SPI_delay);
		if (data & 1<<i)
		gpio_set_gpio_pin(SPI_SDO_PIN);  //MOSI
		else
		gpio_clr_gpio_pin(SPI_SDO_PIN);
		delay(SPI_delay);
		gpio_set_gpio_pin(SPI_SCK_PIN); //SCK pulse
		delay(SPI_delay);
	}
	delay(SPI_delay);
	gpio_set_gpio_pin(SPI_CS_PIN); //CS
	delay(SPI_delay);
}
