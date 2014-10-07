#ifndef SPACE_BASH_THREAD
#define SPACE_BASH_THREAD

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class SpaceBashThread {
public:
	SpaceBashThread(LPTHREAD_START_ROUTINE callback) : m_running(false),
		hThread(INVALID_HANDLE_VALUE), m_callback(callback) {}

	~SpaceBashThread() {
		if (m_running)
			Join();
	}

	void Start() {
		hThread = CreateThread(NULL, 0, m_callback, NULL, 0, NULL);
		m_running = true;
	}
	void Join() {
		if (m_running)
			m_running = false;

		WaitForSingleObject(hThread, INFINITE);
		CloseHandle(hThread);
		hThread = INVALID_HANDLE_VALUE;
	}

	void Delay(DWORD millis) {
		// Try to delay for |millis| time duration.
		// This is called from within the threading function (callback)
		// So it's safe to sleep in the calling thread.
		Sleep(millis);
	}
protected:
	bool m_running;
	HANDLE hThread;
	LPTHREAD_START_ROUTINE m_callback;
	//some protected stuff.
};
#endif