#include <stdio.h>
#include "event_handler.hpp"

void delegator__process_A(string data) {
	fprintf(stderr, "%s() delegator's data: %s\n", __FUNCTION__, data.c_str());
};

void cb__test(void *data) {
	fprintf(stderr, "%s() callback's data: %s\n", __FUNCTION__, data);
};

int main(int argc, char **argv)
{
	// 1. INIT
	EventHandler<delegator_t, string> *g_delegator_listeners = new EventHandler<delegator_t, string>();
	EventHandler<callback_t, void*> *g_callback_listeners = new EventHandler<callback_t, void*>();
	EventHandler<lambda_t, void*> *g_lambda_listeners = new EventHandler<lambda_t, void*>(); 

	// 2. CREATE
	string message = R"({"message" : 123 })";
	g_delegator_listeners->register_event("delegator test", delegator__process_A, message);
	string data = R"({"data" : 123 })";
	g_delegator_listeners->register_event("delegator test2", delegator__process_A, data);
	g_callback_listeners->register_event("callback test", cb__test, (void*)"123");
	g_lambda_listeners->register_event("lambda test", [](void* data){
		fprintf(stderr, "%s() fn's data: %s\n", __FUNCTION__, data);
	}, (void*)"123");

	// 3. RUN
	g_delegator_listeners->rewind_event();
	g_delegator_listeners->rewind_event();
	// g_delegator_listeners->action_event();
	// g_delegator_listeners->filter_event("delegator test");

	// 4. DONE
	delete g_delegator_listeners;
	delete g_callback_listeners;
	delete g_lambda_listeners;
	return 0;
}