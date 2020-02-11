/*****************************************************************************
 * Joseph Zambreno
 * Phillip Jones
 *
 * Department of Electrical and Computer Engineering
 * Iowa State University
 *****************************************************************************/

/*****************************************************************************
 * nes_bootloader.c - main nes_bootloader application code. The bootloader
 * reads a .nes file from the SD card, and uses this information to
 * load and emulate the NES rom.
 *
 *
 * NOTES:
 * 10/25/13 by JAZ::Design created.
 *****************************************************************************/

#include "nes_bootloader.h"
#include "NESCore.h"
#include "ff.h"
#include <unistd.h>  // for usleep

#define THUMB_MEMOFFSET	((WIDTH*135) + 359)

#define BTNS_BASEADDR	0x41210000
#define SWS_BASEADDR	0x41220000
#define JOY_BASEADDR	0x41240000

int bitmapTableSize = 126;
int bitmapCursorIndex = 123;	//index of zelda by default
char bitmapTable[][40] = {
	"1943",
	"advIlnd2",
	"advlolo3",
	"anticip",
	"archon",
	"archriv",
	"astyanax",
	"batman",
	"bioniccm",
	"blastmst",
	"bldsteel",
	"bombman",
	"bombman2",
	"bsbllstr",
	"btoaddd",
	"btoads",
	"bubblbob",
	"californ",
	"castle",
	"castle2",
	"castle3",
	"caveman",
	"chipndal",
	"cobratri",
	"connors",
	"contra",
	"crystlis",
	"dbldrag",
	"dbldrag2",
	"dbldrag3",
	"dkong",
	"dmonswrd",
	"dodge",
	"dragwar",
	"dragwar3",
	"dragwar4",
	"dribble",
	"drmario",
	"ducktale",
	"dusty",
	"faxanadu",
	"finlfant",
	"gargyle2",
	"gaunt",
	"gaunt2",
	"ghostgob",
	"goonies2",
	"gradius",
	"guardleg",
	"hockey",
	"iceclimb",
	"ikari",
	"immortal",
	"ISUBros",
	"jackal",
	"jsilius",
	"kickle",
	"kidicaru",
	"kidniki",
	"kirbyadv",
	"klax",
	"kungfu",
	"lgndwing",
	"lifeforc",
	"litnemo",
	"litsamsn",
	"loderunr",
	"maniacm",
	"mariobro",
	"megaman",
	"megaman2",
	"megaman3",
	"megaman4",
	"megaman5",
	"megaman6",
	"metalger",
	"metlstrm",
	"metroid",
	"mickeyms",
	"micmachn",
	"mspac",
	"ninja",
	"ninja2",
	"offroad",
	"olympus",
	"paperboy",
	"powerbld",
	"qix",
	"radracer",
	"rampage",
	"rbi",
	"rcproam",
	"ringking",
	"rivrcity",
	"rushatck",
	"rygar",
	"sectionz",
	"shwgate",
	"sk8die2",
	"smario2",
	"smario3",
	"snakerat",
	"spider",
	"spyhuntr",
	"ssvball",
	"startrop",
	"stinger",
	"superc",
	"supmario",
	"tecmo",
	"tetris",
	"tmnt",
	"tmnt2",
	"tmnt3",
	"tsupbowl",
	"twrestli",
	"tyson",
	"vice",
	"willow",
	"wizrdwar",
	"worldcup",
	"wwoods",
	"xcitebik",
	"zelda",
	"zelda2",
	"zombie"
};
char fileExtNes[] = ".nes";
char fileExtBmp[] = ".bmp";

// See nes_bootloader.h for configuration options

// Main function. Performs Xilinx-specific initialization, and then goes into the main polling loop
int main() {

	// Initialize all memory space
	xil_init();

	// Initialize the NESCore
	NESCore_Init();


	// Enable the cache
    Xil_DCacheEnable();


    // Main polling loop. For now, you can hard-code the .nes ROM you would like to load.
    // Later, improve the code to have user-specified entry and exit options
    uint8_t nes_fname[40];
	while (1) {
#ifdef GAME_BOOTLOADER
		nes_bootloader_run(nes_fname);
#else
		nes_strncpy(nes_fname, "zelda.nes", 40);
#endif
		nes_load(nes_fname);
	}

}



// Runs the main NES emulation
void nes_load(uint8_t *nes_fname) {

	int32_t result = 0, i;

	usleep(100000);

	if (bootstate.debug_level >= 1)
		xil_printf("nes_load(): loading %s\r\n", nes_fname);


	// Disable the cache so it will play nice with xilsd (needed here)
	Xil_DCacheDisable();
	result = NESCore_LoadROM(nes_fname);
	if (result != 0) {
		xil_printf("nes_load(): invalid ROM load. Returning\r\n");
	}
	// Enable the cache for performance reasons
    Xil_DCacheEnable();



	result = NESCore_Reset();
	if (result != 0) {
		xil_printf("nes_load(): invalid reset. Returning\r\n");
	}

	if (bootstate.debug_level >= 1)
		xil_printf("nes_load(): beginning emulation of %s\r\n", nes_fname);


	bootstate.nes_playing = 1;
	usleep(100000);
	ptv = 0;

	// Runs the emulator 20 cycles at a time. Exits if SW7 is flipped on.
	int exitNES = 0;
	do {

		for (i = 0; i < RESET_TIME; i++) {
			NESCore_Cycle();
		}

		exitNES = *((unsigned int *) SWS_BASEADDR) & 0x80;	//read SW7

	} while (!exitNES);


	bootstate.nes_playing = 0;

	return;

}



// Runs the custom game-selection menu
void nes_bootloader_run(uint8_t *nes_fname) {
	usleep(100000);

	//load splash and default thumbnail
	nes_bootloader_loadBgSplash();
	nes_bootloader_loadThumbMask();

	char nes_bmpname[40];
	nes_strncpy(nes_bmpname, bitmapTable[bitmapCursorIndex], 40);
	nes_strncat(nes_bmpname, fileExtBmp, 40);
	nes_bootloader_loadThumbnail(nes_bmpname);

	int exit = 0;
	int acounter = 0;
	int prev_dpad_state = 0;
	do {
		//capture user inputs
		XGpioPs GpioPs;
		XGpioPs_Config *ConfigPtr;
		ConfigPtr = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
		XGpioPs_CfgInitialize(&GpioPs, ConfigPtr, ConfigPtr->BaseAddr);

#ifdef JOYSTICK
		int dpad_state = *((unsigned int *) JOY_BASEADDR);
		dpad_state = ~dpad_state;

		byte d_up = (dpad_state & 0x02);
		byte d_down = (dpad_state & 0x01);
		byte b_a = (dpad_state & 0x40);

		byte prev_d_up = (prev_dpad_state & 0x02);
		byte prev_d_down = (prev_dpad_state & 0x01);
#else
		int dpad_state = *((unsigned int *) BTNS_BASEADDR);

		byte d_up = (dpad_state & 0x10);
		byte d_down = (dpad_state & 0x01);
		byte b_a = XGpioPs_ReadPin(&GpioPs, 51);

		byte prev_d_up = (prev_dpad_state & 0x10);
		byte prev_d_down = (prev_dpad_state & 0x01);
#endif

		//update state
		//scrolling up
		if(d_up && !prev_d_up) {
			bitmapCursorIndex--;

			if(bitmapCursorIndex < 0) {
				bitmapCursorIndex = bitmapTableSize - 1;
			}

			//draw new thumbnail
			nes_strncpy(nes_bmpname, bitmapTable[bitmapCursorIndex], 40);
			nes_strncat(nes_bmpname, fileExtBmp, 40);
			nes_bootloader_loadThumbnail(nes_bmpname);

		}
		//scrolling down
		else if(d_down && !prev_d_down) {
			bitmapCursorIndex++;

			if(bitmapCursorIndex >= bitmapTableSize) {
				bitmapCursorIndex = 0;
			}

			//draw new thumbnail
			nes_strncpy(nes_bmpname, bitmapTable[bitmapCursorIndex], 40);
			nes_strncat(nes_bmpname, fileExtBmp, 40);
			nes_bootloader_loadThumbnail(nes_bmpname);
		}

		//if A button pressed for a while, exit bootloader and begin game
		if(b_a) {
			acounter++;
		}
		else {
			acounter = 0;
		}

		if(acounter > 60) {
			exit = 1;
		}

		//update controller state for next iteration
		prev_dpad_state = dpad_state;
	} while(!exit);

	//grab name of selected ROM and return
	nes_strncpy(nes_fname, bitmapTable[bitmapCursorIndex], 40);
	nes_strncat(nes_fname, fileExtNes, 40);
	return;
}


//loads "bgsplash.bmp" from SD card and stores it at BBUFFER_BASEADDR
static void nes_bootloader_loadBgSplash() {
	FIL *fp = NULL;

	// Disable the cache so it will play nice with xilsd (needed here)
	Xil_DCacheDisable();

	//load splash bitmap
	xilsd_fopen(fp, "bgsplash.bmp");
	bmpRead(fp, (uint32_t *) SPLASH_BASEADDR);
	xilsd_fclose(fp);

	// Enable the cache for performance reasons
	Xil_DCacheEnable();

	//draw splash
	nes_pixelcpy((uint32_t *) SPLASH_BASEADDR, WIDTH, HEIGHT, 0, (uint16_t *) FBUFFER_BASEADDR, 0, NULL);
}

static void nes_bootloader_loadThumbMask() {
	FIL *fp = NULL;

	// Disable the cache so it will play nice with xilsd (needed here)
	Xil_DCacheDisable();

	//load splash bitmap
	xilsd_fopen(fp, "bgmask.bmp");
	bmpRead(fp, (uint32_t *) MASK_BASEADDR);
	xilsd_fclose(fp);

	// Enable the cache for performance reasons
	Xil_DCacheEnable();
}

static void nes_bootloader_loadThumbnail(uint8_t *nes_bmpname) {
	FIL *fp = NULL;

	// Disable the cache so it will play nice with xilsd (needed here)
	Xil_DCacheDisable();

	//load thumbnail bitmap
	xilsd_fopen(fp, nes_bmpname);
	bmpRead(fp, (uint32_t *) BMP_BASEADDR);
	xilsd_fclose(fp);

	// Enable the cache for performance reasons
	Xil_DCacheEnable();

	//draw image
	nes_pixelcpy((uint32_t *) BMP_BASEADDR, BMP_WIDTH, BMP_HEIGHT, 0, (uint16_t *) FBUFFER_BASEADDR + THUMB_MEMOFFSET, WIDTH - BMP_WIDTH, (uint32_t *) MASK_BASEADDR);
}





// Initializes bootloader state, the Xilinx peripherals, and the front buffer
void xil_init() {

	XStatus Status = XST_SUCCESS;
	uint32_t i;
	uint16_t *ptr;

	// Setup the bootloader state variables.
	bootstate.nes_playing = 0;
	bootstate.activeBuffer = (uint32_t *)FBUFFER_BASEADDR;


	bootstate.debug_level = 1;

	// For now, we disable the DCache as it causes problems with xilsd and vdma
	Xil_DCacheDisable();


	// Initialize the PS GPIO module
	if (bootstate.debug_level >= 1)
		print("xil_init(): Initializing PS gpio module\r\n");

	XGpioPs GpioPs;
	XGpioPs_Config *ConfigPtr;
    ConfigPtr = XGpioPs_LookupConfig(XPAR_XGPIOPS_0_DEVICE_ID);
    XGpioPs_CfgInitialize(&GpioPs, ConfigPtr, ConfigPtr->BaseAddr);
    XGpioPs_SetDirectionPin(&GpioPs, 50, 0);	//MIO50 is B
    XGpioPs_SetDirectionPin(&GpioPs, 51, 0);	//MIO51 is A

	// Initialize the VTC module
	if (bootstate.debug_level >= 1)
		print("xil_init(): Initializing v_tc module\r\n");

	VtcCfgPtr = XVtc_LookupConfig(XPAR_V_TC_0_DEVICE_ID);
	XVtc_CfgInitialize(&Vtc, VtcCfgPtr, VtcCfgPtr->BaseAddress);
	XVtc_EnableGenerator(&Vtc);


	// Initialize the front buffer
	if (bootstate.debug_level >= 1)
		print("xil_init(): Initializing front buffer\r\n");

	// Initialize the framebuffer. We can overwrite the edges with 0s.
	ptr = (uint16_t *)FBUFFER_BASEADDR;
	for (i = 0; i < WIDTH*HEIGHT; i++) {
		ptr[i] = INIT_COLOR;
		if (i % WIDTH == 0)
			ptr[i] = 0;
	}

	// Initialize the back buffer
	if (bootstate.debug_level >= 1)
		print("xil_init(): Initializing back buffer\r\n");

	ptr = (uint16_t *)BBUFFER_BASEADDR;
	for (i = 0; i < WIDTH*HEIGHT; i++) {
		ptr[i] = INIT_COLOR;
		if (i % WIDTH == 0)
			ptr[i] = 0;
	}

	// Initialize the VDMA module
	if (bootstate.debug_level >= 1)
		print("xil_init(): Initializing vdma module\r\n");


    // Set up VDMA config registers. Copy-paste solution from vga_test.c (but note difference in framebuffer start address)
    XAxiVdma_WriteReg(XPAR_AXI_VDMA_0_BASEADDR, XAXIVDMA_CR_OFFSET, 0x3);  // Circular Mode and Start bits set, VDMA MM2S Control
    XAxiVdma_WriteReg(XPAR_AXI_VDMA_0_BASEADDR, XAXIVDMA_HI_FRMBUF_OFFSET, 0x0);  // VDMA MM2S Reg_Index
    XAxiVdma_WriteReg(XPAR_AXI_VDMA_0_BASEADDR, XAXIVDMA_FRMSTORE_OFFSET, 1);  // VDMA MM2S Number FRM_Stores
    XAxiVdma_WriteReg(XPAR_AXI_VDMA_0_BASEADDR, XAXIVDMA_MM2S_ADDR_OFFSET + XAXIVDMA_START_ADDR_OFFSET, (u32) FBUFFER_BASEADDR);  // VDMA MM2S Start Addr 1
    XAxiVdma_WriteReg(XPAR_AXI_VDMA_0_BASEADDR, XAXIVDMA_MM2S_ADDR_OFFSET + XAXIVDMA_STRD_FRMDLY_OFFSET, 640*2);  // 1280 bytes, VDMA MM2S FRM_Delay, and Stride
    XAxiVdma_WriteReg(XPAR_AXI_VDMA_0_BASEADDR, XAXIVDMA_MM2S_ADDR_OFFSET + XAXIVDMA_HSIZE_OFFSET, 640*2);  // 1280 bytes, VDMA MM2S HSIZE
    XAxiVdma_WriteReg(XPAR_AXI_VDMA_0_BASEADDR, XAXIVDMA_MM2S_ADDR_OFFSET + XAXIVDMA_VSIZE_OFFSET, 480);  // 480 lines, VDMA MM2S VSIZE  (Note: Starts VDMA transaction


  	return;
}


