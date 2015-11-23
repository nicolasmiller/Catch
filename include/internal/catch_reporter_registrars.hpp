/*
 *  Created by Phil on 31/12/2010.
 *  Copyright 2010 Two Blue Cubes Ltd. All rights reserved.
 *
 *  Distributed under the Boost Software License, Version 1.0. (See accompanying
 *  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#ifndef TWOBLUECUBES_CATCH_REPORTER_REGISTRARS_HPP_INCLUDED
#define TWOBLUECUBES_CATCH_REPORTER_REGISTRARS_HPP_INCLUDED

#include "catch_interfaces_registry_hub.h"

namespace Catch {

    template<typename T>
    class ReporterRegistrar {

        class ReporterFactory : public SharedImpl<IReporterFactory> {

            virtual IStreamingReporter* create( ReporterConfig const& config ) const {
                return new T( config );
            }

            virtual std::string getDescription() const {
                return T::getDescription();
            }
        };

    public:

        ReporterRegistrar( std::string const& name ) {
            getMutableRegistryHub().registerReporter( name, new ReporterFactory() );
        }
    };

    template<typename T>
    class ListenerRegistrar {

        class ListenerFactory : public SharedImpl<IReporterFactory> {

            virtual IStreamingReporter* create( ReporterConfig const& config ) const {
                return new T( config );
            }
            virtual std::string getDescription() const {
                return "";
            }
        };

    public:

        ListenerRegistrar() {
            getMutableRegistryHub().registerListener( new ListenerFactory() );
        }
    };
}

#define INTERNAL_CATCH_REGISTER_REPORTER( name, reporterType ) \
    namespace{ Catch::ReporterRegistrar<reporterType> catch_internal_RegistrarFor##reporterType( name ); }

#define INTERNAL_CATCH_REGISTER_LISTENER( listenerType ) \
    namespace{ Catch::ListenerRegistrar<listenerType> catch_internal_RegistrarFor##listenerType; }

#endif // TWOBLUECUBES_CATCH_REPORTER_REGISTRARS_HPP_INCLUDED
