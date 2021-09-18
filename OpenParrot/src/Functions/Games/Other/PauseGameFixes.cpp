#include <StdInc.h>
#include "Utility/GameDetect.h"
#include "Utility/InitFunction.h"
#include "Functions/Global.h"
#include "Utility/Helper.h"

bool PauseEnabled;
static bool PauseGameFixInit;
static DWORD TimerValue;

void PauseGameFixes(Helpers* helpers)
{
	if (!PauseEnabled)
		PauseEnabled = true;

	if (GameDetect::currentGame == GameID::SR3)
	{
		if (!PauseGameFixInit)
		{
			PauseGameFixInit = true;
			TimerValue = helpers->ReadIntPtr(0x9C4A07, false);
		}
		helpers->WriteIntPtr(0x9C4A07, TimerValue, false);
	}

	if (GameDetect::currentGame == GameID::DirtyDrivin)
		helpers->WriteByte(0x99D894, 0x01, false);

	if (GameDetect::currentGame == GameID::H2Overdrive)
	{
		helpers->WriteByte(0x1F86D, 0x00, true);
		helpers->WriteByte(0x1F870, 0x00, true);
	}
}

void ResetPauseGameFixes(Helpers* helpers)
{
	PauseEnabled = false;

	if (GameDetect::currentGame == GameID::SR3)
		PauseGameFixInit = false;

	if (GameDetect::currentGame == GameID::DirtyDrivin)
		helpers->WriteByte(0x99D894, 0x00, false);

	if (GameDetect::currentGame == GameID::H2Overdrive)
	{
		helpers->WriteByte(0x1F86D, 0x01, true);
		helpers->WriteByte(0x1F870, 0x01, true);
	}
}