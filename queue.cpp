
#include "queue.h"

// TODO: Implement everything from the queue class here, along with
// testqueue ... we are only providing checkinvariant
bool queue::checkinvariant( ) const {
	if( current_size == 0 )
	{
    	if( first ) 
    	{
        	std::cout << "INVARIANT: ";
        	std::cout << "current_size == 0, but first != nullptr\n";
        	return false;
    	}

    	if( last )
    	{
        	std::cout << "INVARIANT: ";
        	std::cout << "current_size == 0, but last != nullptr\n";
        	return false;
    	}

    	return true;
   }
 
   size_t s = 0;
   const qnode* l = nullptr; // This will remember the last node.

   for( const qnode* p = first; p; p = p -> next ) 
   {
    	if( s == current_size )
    	{
   			std::cout << "INVARIANT: ";
        	std::cout << "current_size is less than real size: ";
        	std::cout << current_size << "\n\n"; 
    		// I don't want to count further because list may be corrupt. 
    		return false;
    	}
    	++ s;  
    	l = p; 
   }

   if( s != current_size )
   {
		std::cout << "INVARIANT ";
    	std::cout << "current_size is not equal to real size\n";
    	std::cout << "current_size = " << current_size << "\n";
    	std::cout << "real size    = " << s << "\n";

    	return false;
   }

   if( l != last )
   {
    	std::cout << "INVARIANT: last is not correct, ";
    	std::cout << "it is " << last << " but must be " << l << "\n";
    	return false;
   }

   return true; 
} 

queue::queue( ) : // done
	first(nullptr),
	last(nullptr),
	current_size(0)
{	

}

queue::queue( const queue& q ) : //done i guess except for fields
	first (nullptr),
	last(nullptr),
	current_size(0)
{
	qnode* node = q.first;
	while (node != NULL) {
		push(node->val);
		node = node->next;
	}
}

const queue& queue::operator = ( const queue& q ) { //done
	clear();
	qnode* node = q.first;
	while (node != NULL) {
		push(node->val);
		node = node->next;
	}
	return *this;
}

queue::~queue( ) { // done
	clear();
}

queue::queue( std::initializer_list<double> init ) ://seems to be done except fields
// So that you can write q = { 1,2,3 };
// You can use init. size( ) to see the size, and
// for( double d : init ) to go through all
// elements in the initializer_list.
	first(nullptr),
	last(nullptr),
	current_size(0)
{
	size_t i = 0;
	for (double d : init) {
		push(d);
		i++;
	}
}

void queue::push( double d ) {//definitely done
	qnode* new_node = new qnode(d); // create a new temporary variable of type struct qnode with a value d
	if (current_size == 0)  { // if queue is empty
		first = new_node; // assign both first and last as temp
		last = new_node;
	} // in all the other situations
	last->next = new_node; // change the next of the previous last node to newly added node
	last = new_node; // new node is tail now
	current_size++; // increment size
}

void queue::pop( ) { // done
	qnode* old_head = first;
	if (current_size == 0) {
		throw std::runtime_error( "pop: queue is empty" );
	} else if (current_size == 1) {
		first = NULL;
		last = NULL;
		delete old_head;
	} else {
		first = first->next;
		delete old_head;
	}
	current_size--;
}

void queue::clear( ) { // done
	qnode* node = first;
	while (node != NULL) {
		pop();
		node = node->next;
	}
}

double queue::peek( ) const { // done
	if (current_size == 0) {
		throw std::runtime_error( "peek: queue is empty" );
	} else {
		return first->val;
	}
}

void queue::print( std::ostream& out) const { //seems to be done
	qnode* node = first;
	out << "[";
	while (node != NULL) {
		out << node->val;
		node = node->next;
	}
	out << "]";
}

inline std::ostream& operator << ( std::ostream& out, const queue& q ) // done
{
	q. print( out );
	return out;
}

void testqueue( )
{
	// Default construction
	std::cout << "\nDefault-construct queue 1\n";
	queue q1;
	q1.checkinvariant();
  
	// Repetitive pushing
	std::cout << "\nEnter pushing for-loop for queue 1\n";
	double sign = 1;
	for(size_t i = 1; i <= 10; i++) {
		sign = (-1)*sign;
		q1.push(sign*((i*i)/10.0));
		std::cout << "Pushed " << sign*((i*i)/10.0) << "\n";
		q1.checkinvariant();  
  }
  
	// Copy construction 1
	std::cout << "\nCopy-construct queue 2 from queue 1 using standard function\n";
	queue q2(q1);
	std::cout << "Queue 2 is " << q2 << "\n";
	q2.checkinvariant();
  
	// Copy construction 2
	std::cout << "\nCopy-construct queue 3 from queue 2 using assignment operator\n";
	queue q3 = q2;
	std::cout << "Queue 3 is " << q3 << "\n"; 
	q3.checkinvariant();

	// Initializer-list construction
	std::cout << "\nInitializer-list-construct queue 4\n";
	queue q4 = {100, 485, 500, 300, 401, 848, 646, 134, 891, 327};
	std::cout << "Queue 4 is " << q4 << "\n";
	q4.checkinvariant();

	// Assignment of a queue with the same size as the left hand side
	std::cout << "\nAssign values of queue 4 to queue 2 (both have the same size)\n";
	q2 = q4;
	std::cout << "Queue 2 is " << q2 << "\n";
	q2.checkinvariant();

	// Repetitive peeking & popping
	std::cout << "\nEnter peeking & popping for-loop for queue 2\n";
	for(size_t j = 1; j <= 9; j++) {
		std::cout << "Element " << j << " is " << q2.peek() << "\n";
		q2.pop();
		std::cout << "Popped\n";
		q2.checkinvariant();
	}

	// Initializer-list construction
	std::cout << "\nInitializer-list-construct queue 5\n";
	queue q5 = {1000000, 99, 19};
	std::cout << "Queue 5 is " << q5 << "\n";
	q5.checkinvariant();

	// Assignment
	std::cout << "\nAssign values of queue 4 to queue 2\n";
	q4 = q3;
	std::cout << "Queue 4 is " << q4 << "\n";
	q4.checkinvariant();

	// Self-assignment
	std::cout << "\nSelf-assign queue 4 to queue 4\n";
	q4 = q4;
	std::cout << "Queue 4 is " << q4 << "\n";
	q4.checkinvariant();

	// Reconstruction
	std::cout << "\nReconstruct queue 4 using initializer-list-constructor\n";
	q4 = {-1.444, 2.55555, -3.6666666};
	std::cout << "Queue 4 is " << q4 << "\n";
	q4.checkinvariant();

	// Clearing & printing
	std::cout << "\nClear queue 1\n";
	q1.clear();
	std::cout << "Queue 1 is " << q1 << "\n";
	q1.checkinvariant();

	// Printing
	std::cout << "\nResults of tests\n";
	std::cout << "Queue 1 is " << q1 << "\n";
	q1.checkinvariant();
	std::cout << "Queue 2 is " << q2 << "\n";
	q2.checkinvariant();
	std::cout << "Queue 3 is " << q3 << "\n";
	q3.checkinvariant();
	std::cout << "Queue 4 is " << q4 << "\n";
	q4.checkinvariant();
}


