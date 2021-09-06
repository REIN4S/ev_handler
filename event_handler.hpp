#include <stdio.h>
#include "event_handler.hpp"

typedef function<void(string)>   delegator_t;
typedef function<void(void*)>   callback_t;
typedef function<void(void*)>     lambda_t;
EventHandler<delegator_t, string> *g_delegator_listeners;
EventHandler<callback_t, void*> *g_callback_listeners;
EventHandler<lambda_t, void*> *g_lambda_listeners;
void run();

void delegator__process_A(string data) {
	fprintf(stderr, "%s() delegator's data: %s\n", __FUNCTION__, data.c_str());
};

void cb__test(void* data) {
	fprintf(stderr, "%s() callback's data: %d\n", __FUNCTION__, data);
};

int main(int argc, char **argv)
{
	// 1. INIT
	g_delegator_listeners = new EventHandler<delegator_t, string>();
	g_callback_listeners = new EventHandler<callback_t, void*>();
	g_lambda_listeners = new EventHandler<lambda_t, void*>(); 

	// 2. CREATE
	g_delegator_listeners->register_event("delegator test", delegator__process_A, R"({"message" : 123 })");
	// g_delegator_listeners->register_event("delegator test2", delegator__process_A, R"({"data" : 123 })");
	g_callback_listeners->register_event("callback test", cb__test);
	g_callback_listeners->register_event("callback test2", cb__test);
	g_callback_listeners->register_event("callback test3", cb__test);
	string capture = "captured data";
	g_lambda_listeners->register_event("lambda test", [&capture](void* data){
		fprintf(stderr, "%s() lambda's data: %s \t and captured data: %s\n", __FUNCTION__, data, capture.c_str());
	}, (void*)"123");

	// 3. RUN
	run();	

	// 4. DONE
	delete g_delegator_listeners;
	delete g_callback_listeners;
	delete g_lambda_listeners;
	return 0;
}

void run() {
	cout << "delegator - FIRST" << endl;
	g_delegator_listeners->rewind_event();
	cout << "delegator - SECOND" << endl;
	g_delegator_listeners->rewind_event();

	cout << "callback - FIRST" << endl;
	g_callback_listeners->rewind_event((void*)123);

	cout << "lambda - FIRST" << endl;
	g_lambda_listeners->rewind_event();
	g_lambda_listeners->rewind_event((void*)"asdf");
}
