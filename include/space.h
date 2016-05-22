// 
// Author: Matej Zavrsnik (matejzavrsnik.com)
//

#ifndef SPACE_H
#define	SPACE_H

#include <vector>
#include <map>
#include "vector.h"
#include "body.h"
#include "consts.h"
#include "quadtree.h"
#include "laws.h"

namespace mzlib
{
    class cspace
    {
        
    public:
        
        typedef std::shared_ptr<cspace> ptr;
        
        // TODO: A monstrosity!! Space dimensions are undefined. Make quadtree dynamic at some point
        cspace(
            const mzlib::math::cvector2d& top_left, 
            const mzlib::math::cvector2d& bottom_right, 
            const double smallest_node_width) 
            : 
            m_bodies(
                top_left,
                bottom_right,
                smallest_node_width)
        {
        }

        cspace()
            : 
            m_bodies(
                {-10e50,-10e50},
                { 10e50, 10e50},
                10e50/2-1)
        {
        }
        cspace(const cspace&) = default;
        cspace(cspace && ) = default;
        cspace& operator=(const cspace&) = default;
        cspace& operator=(cspace&&) = default;
        ~cspace() = default;
        

        void add_body(std::shared_ptr<cbody> body) {
            //m_bodies.push_back(body);
            m_bodies.add(body, body->get_location());
        }
        
        cquadtree<std::shared_ptr<cbody>>& get_bodies()
        {
            return m_bodies;
        }
        
        void set_gravitational_constant(double gravitational_constant) {
            m_gravitational_constant = gravitational_constant;
        }
        
        double get_gravitational_constant() const {
            return m_gravitational_constant;
        }
        
        void set_law_of_gravitation(interface_law_of_gravitation new_law) 
        {
            m_fun_law_of_gravitation = new_law;
        }
        
        void calculate_forces() {
            for(auto this_body : m_bodies) {
                this_body->set_force({0.0,0.0});
                for(auto another_body : m_bodies) {
                    if(this_body != another_body) {
                        math::cvector2d gravity_force = m_fun_law_of_gravitation(this_body.get(), another_body.get(), m_gravitational_constant);
                        this_body->add_force(gravity_force);
                    }
                }
            }
        }
        
        void calculate_positions(double time_pixel) {
            for(auto body : m_bodies) {
                math::cvector2d velocity_initial = body->get_velocity();
                math::cvector2d acceleration{0};
                acceleration = body->get_force() / body->get_mass();
                math::cvector2d velocity_final = velocity_initial + acceleration * time_pixel;
                if(velocity_final.length() > m_max_velocity) {
                    acceleration = {0.0,0.0};
                    velocity_final = velocity_initial;
                }
                math::cvector2d location_final = (velocity_initial*time_pixel) + (acceleration*time_pixel)/2; 
                body->add_location(location_final);
                body->set_velocity(velocity_final);
            }
        }
        
        void forward_time(double seconds, double time_pixel) {
            // Time pixel idea stems from the fact that calculations are done in discreet time intervals.
            // If it is about some linear motion it doesn't matter, but if you are trying to calculate other
            // motions, particularly if over larger span of time, you might get dramatically different results
            // if you don't break the time in smaller chunks, time pixels. This way you can forward_time for
            // instance to one year in the future, but retain positions and forces recalculations on every 0.1 
            // seconds to minimise the error. Of course, you could as well call a function in a loop for a couple 
            // of times, but isn't it nicer to simply operate with points in time and not think about the rest?
            for(double time=0; time<seconds; time += time_pixel)
            {
                calculate_positions(time_pixel);
                calculate_forces();
            }
        }
        
    private:
        
        cquadtree<std::shared_ptr<cbody>> m_bodies;
        double m_gravitational_constant = consts::gravitational_constant;
        double m_max_velocity = consts::light_speed;
        interface_law_of_gravitation m_fun_law_of_gravitation = universal_law_of_gravitation;//fun_universal_law_of_gravitation;
        
    };

}

#endif	/* SPACE_H */

