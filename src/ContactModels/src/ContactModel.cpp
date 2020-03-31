/**
 * @file ContactModel.cpp
 * @authors Giulio Romualdi
 * @copyright 2020 Istituto Italiano di Tecnologia (IIT). This software may be modified and
 * distributed under the terms of the GNU Lesser General Public License v2.1 or any later version.
 */

#include <BipedalLocomotionControllers/ContactModels/ContactModel.h>

using namespace BipedalLocomotionControllers::ContactModels;

bool ContactModel::initialize(std::weak_ptr<ParametersHandler::IParametersHandler> handler)
{
    // the parameters has been update the previous quantities has to be evaluated again
    m_isContactWrenchComputed = false;
    m_isControlMatrixComputed = false;
    m_isAutonomousDynamicsComputed = false;

    return initializePrivate(handler);
}

void ContactModel::setState(const iDynTree::Twist& twist,
                            const iDynTree::Transform& transform,
                            const iDynTree::Transform& nullForceTransform)
{
    // the state has been update the previous quantities has to be evaluated again
    m_isContactWrenchComputed = false;
    m_isControlMatrixComputed = false;
    m_isAutonomousDynamicsComputed = false;

    setStatePrivate(twist, transform, nullForceTransform);

    return;
}

const iDynTree::Wrench& ContactModel::getContactWrench()
{
    if (!m_isContactWrenchComputed)
    {
        computeContactWrench();
        m_isContactWrenchComputed = true;
    }

    return m_contactWrench;
}

const iDynTree::Vector6& ContactModel::getAutonomousDynamics()
{
    if (!m_isAutonomousDynamicsComputed)
    {
        computeAutonomousDynamics();
        m_isAutonomousDynamicsComputed = true;
    }

    return m_autonomousDynamics;
}

const iDynTree::Matrix6x6& ContactModel::getControlMatrix()
{
    if (!m_isControlMatrixComputed)
    {
        computeControlMatrix();
        m_isControlMatrixComputed = true;
    }

    return m_controlMatrix;
}