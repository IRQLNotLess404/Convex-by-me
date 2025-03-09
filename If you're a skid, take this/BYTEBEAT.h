HWAVEOUT hwo;

namespace Bytebeat {
	DWORD Sound1(VOID) {
		BYTE tbuffer[24000 * 30];
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 24000, 24000, 1, 8, 0};
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)(127*sin(t&(t>>5^t>>9)>>4)+128);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutSetVolume(hwo, 0xffffffff);
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Sound2(VOID) {
		BYTE tbuffer[32000 * 25];
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)(2*sin(t/14^(t/9>>5)&t>>10));
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutSetVolume(hwo, 0xffffffff);
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Sound3(VOID) {
		BYTE tbuffer[32000 * 20];
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 48000, 48000, 1, 8, 0};
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)((t*(t&t>>12)^t)/127);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutSetVolume(hwo, 0xffffffff);
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Sound4(VOID) {
		BYTE tbuffer[32000 * 30];
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 48000, 48000, 1, 8, 0};
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)((t/5&128)+(t&t>>10)*12);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutSetVolume(hwo, 0xffffffff);
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Sound5(VOID) {
		BYTE tbuffer[32000 * 25];
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 33000, 33000, 1, 8, 0};
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)(((2*tan(t>>2|365)-3)*128)+(t>>1));
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutSetVolume(hwo, 0xffffffff);
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Sound6(VOID) {
		BYTE tbuffer[32000 * 20];
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 33000, 33000, 1, 8, 0};
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)((t*(t>>5&3)>>7)*t);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutSetVolume(hwo, 0xffffffff);
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Sound7(VOID) {
		BYTE tbuffer[32000 * 30];
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 48000, 48000, 1, 8, 0};
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)((t>>5|t>>4)*(t>>7|t>>3)+t);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutSetVolume(hwo, 0xffffffff);
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
	
	DWORD Noise(VOID) {
		BYTE tbuffer[32000 * 15];
		WAVEFORMATEX wfx = {WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0};
		waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 1, 0, CALLBACK_NULL);
		for (ULONG t = 0; t < sizeof(tbuffer); t++) {
			tbuffer[t] = (BYTE)(t*rand()|(t<<3)&128);
		}
		WAVEHDR wh = {(PSTR)tbuffer, sizeof(tbuffer), 0, 0, 0, 0, 0, 0};
		waveOutSetVolume(hwo, 0xffffffff);
		waveOutPrepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutWrite(hwo, &wh, sizeof(tbuffer));
		waveOutUnprepareHeader(hwo, &wh, sizeof(tbuffer));
		waveOutClose(hwo);
	}
}
