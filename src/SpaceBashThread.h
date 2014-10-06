#ifndef SPACE_BASH_THREAD
#define SPACE_BASH_THREAD

class SpaceBashThread {
public:
	SpaceBashThread(void* callback) : m_running(false) {}
	~SpaceBashThread() {
		if (m_running)
			Join();
	}

	void Start() {
		m_running = true;
	}
	void Join() {
		if (m_running)
			m_running = false;
	}

	void Delay(short millis) {
		// Try to delay for |millis| time duration.
	}
protected:
	bool m_running;
	//some protected stuff.
};
#endif