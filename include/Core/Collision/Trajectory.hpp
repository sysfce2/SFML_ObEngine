#pragma once

#include <functional>
#include <vector>

#include <Collision/PolygonalCollider.hpp>
#include <Transform/UnitVector.hpp>
#include <Transform/Units.hpp>
#include <Types/Togglable.hpp>
#include <Types/Tweenable.hpp>

namespace obe::Collision
{
    class TrajectoryNode;
    class Trajectory;
    class PolygonalCollider;

    using OnCollideCallback
        = std::function<void(Trajectory&, Transform::UnitVector, Collision::CollisionData)>;
    using TrajectoryCheckFunction
        = std::function<void(Trajectory&, Transform::UnitVector&, PolygonalCollider*)>;

    /**
     * \brief A Trajectory makes a TrajectoryNode moves using angle, speed and
     *        acceleration (Linear Trajectory)
     */
    class Trajectory : public Types::Togglable, public Types::Tweenable<3>
    {
    private:
        double m_acceleration = 0;
        double m_angle = 0;
        std::vector<TrajectoryCheckFunction> m_checks {};
        OnCollideCallback m_onCollideCallback;
        double m_speed = 0;
        bool m_static = false;
        Transform::Units m_unit;
        friend class TrajectoryNode;

    public:
        Trajectory(Transform::Units unit = Transform::Units::SceneUnits);
        Trajectory& addAcceleration(double acceleration);
        Trajectory& addAngle(double angle);
        void addCheck(const TrajectoryCheckFunction& check);
        Trajectory& addSpeed(double speed);
        [[nodiscard]] double getAcceleration() const;
        [[nodiscard]] double getAngle() const;
        std::vector<TrajectoryCheckFunction>& getChecks();
        OnCollideCallback& getOnCollideCallback();
        [[nodiscard]] double getSpeed() const;
        [[nodiscard]] bool getStatic() const;
        [[nodiscard]] Transform::Units getUnit() const;
        void onCollide(const OnCollideCallback& callback);
        Trajectory& setAcceleration(double acceleration);
        Trajectory& setAngle(double angle);
        Trajectory& setSpeed(double speed);
        Trajectory& setStatic(bool tStatic);
        void setNumericalComponents(const NumericalComponents& components) override
        {
            m_acceleration = components[0];
            m_angle = components[1];
            m_speed = components[2];
        }

        [[nodiscard]] NumericalComponents getNumericalComponents() override
        {
            return { m_acceleration, m_angle, m_speed };
        }
    };
} // namespace obe::Collision
