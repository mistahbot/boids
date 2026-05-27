#include "System.h"

// 1. Create a global pointer to hold our simulation. 
// WebAssembly needs this to stay alive in memory between JavaScript frames.
System* simulation = nullptr;

// 2. Wrap our bridge functions so JavaScript can see them
extern "C" {

    void init_system(int num_boids) {
        // If a simulation already exists (like if the user clicked "Reset"), delete the old one
        if (simulation != nullptr) {
            delete simulation; 
        }
        // Create a new simulation (passing n boids, and an 'r' value of 2.0)
        simulation = new System(num_boids, 3.5); 
    }

    void simulate_frame() {
        if (simulation != nullptr) {
            simulation->SimulateFrame();
        }
    }

    // 3. The Memory Vault Key!
    double* get_boids_pointer() {
        if (simulation != nullptr && simulation->b.size() > 0) {
            // b[0] is the first boid in your contiguous std::vector
            // We return a pointer to the memory address of its exact starting coordinate
            return &(simulation->b[0].pos.x); 
        }
        return nullptr;
    }

}