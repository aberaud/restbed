/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <string>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>
#include "base_rule.hpp"

//External Includes

//System Namespaces
using std::string;
using std::function;
using std::shared_ptr;

//Project Namespaces
using namespace restbed;

//External Namespaces

class ContentTypeRule : public BaseRule
{
    public:
        ContentTypeRule( void ) : BaseRule( )
        {
            return;
        }

        ContentTypeRule( const ContentTypeRule& original ) : BaseRule( original )
        {
            return;
        }
        
        virtual ~ContentTypeRule( void )
        {
            return;
        }
        
        bool condition( const shared_ptr< Session >& session ) final override
        {
        	return session->get_request( )->has_header( "Content-Type" );
        }

        void action( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback ) final override
        {
        	auto request = session->get_request( );

        	if ( request->get_header( "Content-Type", String::lowercase ) not_eq "application/csv" )
        	{
        		session->close( UNSUPPORTED_MEDIA_TYPE,
        			            "Unsupported Media Type, must be 'application/csv'.",
        			            { { "Content-Length", "50" }, { "Content-Type", "text/plain" } } );
        	}
        	else
        	{
        		callback( session );
        	}
        }
};