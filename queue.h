
#ifndef QUEUE_INCLUDED 
#define QUEUE_INCLUDED  1

#include <iostream>
#include <initializer_list>

// Normally, one would define qnode inside queue:

class queue
{
	struct qnode
	{
		double val;
		qnode* next;    // Next in the queue. 
	
		qnode( double val ) :
	    val( val ),
	    next( nullptr )
		{ }
	};

   size_t current_size; 
   qnode* first;
   qnode* last;

public: 
	queue( );
      
	queue( const queue& q );
   
	const queue& operator = ( const queue& q );
   
	~queue( );

	queue( std::initializer_list<double> init );

	void push( double d );  

	void pop( );
   
	void clear( );

	double peek( ) const;

	size_t size( ) const { return current_size; } 
   
	bool empty( ) const { return current_size == 0; } 
   
	void print( std::ostream& ) const; 

	bool checkinvariant( ) const; 
		// Call this function frequently.   
      
    friend std::ostream& operator << ( std::ostream& out, const queue& q );
}; 

inline std::ostream& operator << ( std::ostream& out, const queue& q );

void testqueue( );
   // Write this function in queue.cpp. It must do some tests on
   // queue. 

#endif


