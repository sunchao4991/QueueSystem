//
// Queue.hpp
// QueueSystem
//

#ifndef Queue_hpp
#define Queue_hpp

#include <iostream>
#include <cstdlib>
#include "Event.hpp"

template <typename T>
class Queue
{
public:
	Queue() {
		this->front = new T;
        	if (!this->front) {
            	exit(-2);
        	}	
        	this->front->next = NULL;
        	this->rear = this->front;
	}	
	
	~Queue() {
        	this->clearQueue();
        	delete this->front;
	}
	
	T* enqueue(T &node) {
        	T *new_node = new T;
        	if (!new_node) {
        	exit(-1);
        	}
        	*new_node = node;
        	this->rear->next = new_node;
        	this->rear = new_node;
        	return this->front;
	}

	T* dequeue() {
		if (!this->front->next) {
        	return NULL;
    	}
		T *temp_node;
    		temp_node = this->front->next;
    		this->front->next = temp_node->next;

    		if (this->rear == temp_node) {
        	this->rear = this->front;
	       	}
		return temp_node;
	}
	
	T* orderEnqueue(Event *event) {
		Event *temp = new Event;
    		if (!temp) {
        	exit(-1);
    		}
    		
		*temp = event;
		if (!this->front->next) {
			this->enqueue(*temp);
        		return this->front;
		}
		Event *temp_event_list = this->front;
		while(temp_event_list->next && temp_event_list->next->occur_time < event.occur_time) {
			temp_event_list = temp_event_list->next;
		}
		temp->next = temp_event_list->next;
    		temp_event_list->next = temp;
		return this->front;
	}
	int length() {
		T *temp_node;
		temp_node = front->next;
		int length = 0;
		while (temp_node) {
			temp_node = temp_node->next;
			++length;
		}
		return length;
	}
	void clearQueue () {
		T *temp_node;
		while (this->front->next) {
			temp_node = this->front->next;
			this->front->next = temp_node->next;
			delete temp_node->next;
		}
		this->front->next = NULL;
		this->rear = this->front;
	}

private:
	T *front;
	T *rear;
};

#endif /* Queue_hpp */
