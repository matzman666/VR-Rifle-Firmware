#pragma once

#define DEBUG_LOG 1

#if DEBUG_LOG == 1
	#define LOG(msg) Serial.write(msg);
#else
	#define LOG(msg)
#endif


