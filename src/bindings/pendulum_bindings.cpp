#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <array>

#include "simulation/pendulum.h"

namespace py = pybind11;

PYBIND11_MODULE(pendulum_pysim, m)
{
    py::class_<simulation::Pendulum>(m, "Pendulum")
        .def(py::init<float, float, float>())
        .def("update", &simulation::Pendulum::update)
        .def("add_force", &simulation::Pendulum::addForce)
        .def("set_state", [](simulation::Pendulum& p,
                             float x, float xdot,
                             float theta, float omega) {
            p.setState(x, xdot, theta, omega);
        })
        .def("get_state", [](const simulation::Pendulum& p) {
            auto s = p.getState();

            py::array_t<float> arr(4);
            auto r = arr.mutable_unchecked<1>();

            r(0) = s.cart_position;
            r(1) = s.cart_velocity;
            r(2) = s.theta;
            r(3) = s.omega;

            return arr;
        });
}
