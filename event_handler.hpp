#include <functional>
#include <string>
#include <iostream>

using namespace std;

typedef function<void(string)>   delegator_t;
typedef function<void(void*)>     callback_t;
typedef function<void(void*)>     lambda_t;

template<typename T, typename T2> class EventHandler {

    private:
        string event_name;
        T callback;
		T2 data;
        class EventHandler* next;
    
	public:
        EventHandler() : event_name(""), callback(NULL), next(NULL) {
			cout << __FUNCTION__ << "() be called." << endl;
		};

        ~EventHandler() {
			cout << __FUNCTION__ << "() be called." << endl;
			if(next != NULL) {
				cout << "delete : " << next->event_name << endl;
				delete next;
			} else {
				cout << "delete this? : " << event_name << endl;
			}
		};

		void register_event(string e_name, T cb, T2 data) {
			cout << __FUNCTION__ << "(" << e_name << ") be called." << endl;
			
			EventHandler* iter = this;
			
			if( !event_name.empty() && callback != NULL ) {
				while( iter->next != NULL ) {
					iter = iter->next;
				}
				iter->next = new EventHandler<T, T2>();
				iter = iter->next;
			} 

			iter->event_name = e_name;
			iter->callback = cb;
			iter->data = data;

		};

		void rewind_event() {
			cout << __FUNCTION__ << "() be called." << endl;
			EventHandler* iter = this;
			do {
				iter = iter->next;
				iter->callback(iter->data);
			} while( iter->next != NULL );
		}

		void action_event() {
			cout << __FUNCTION__ << "() be called." << endl;
		}

		void filter_event(string e_name) {
			cout << __FUNCTION__ << "(" << e_name << ") be called." << endl;
			EventHandler* iter = this;
			do {
				iter = iter->next;
				if(iter->event_name == e_name) iter->callback("TEST iter");
			} while( iter->next != NULL );
		}
};