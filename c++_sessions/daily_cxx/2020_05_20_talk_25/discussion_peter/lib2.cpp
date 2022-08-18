void Register( void* p );
struct B
{
B(){ Register(this); }
} b;
