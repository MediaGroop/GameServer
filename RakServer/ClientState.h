#pragma once

enum ClientState{
	CONNECTED,
	VERIFYING,
	VERIFIED,
	READY_TO_ENTER,
	LOADING_WORLD,
	PLAYING
};