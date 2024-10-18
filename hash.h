#ifndef HASH_HEADER
#define HASH_HEADER

unsigned long one_hash          ( Stack_t* ptr_stk );
bool          hash_check        ( Stack_t* ptr_stk );

#ifdef HASH_PROTECT

    #define GIVE_ME_HASH(ptr_stk )                                                                                                               \
    one_hash ( ptr_stk )

    #define ZABULLIL_HASH( ptr_stk )                                                                                                              \
    hash_check ( ptr_stk )

    #define FREE_HASH( ptr_stk )                                                                                                                  \
    ptr_stk->hehesh = 0
#else
    #define GIVE_ME_HASH( ptr_stk )
    #define ZABULLIL_HASH( ptr_stk )
    #define FREE_HASH( ptr_stk )
#endif

#endif
