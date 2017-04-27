#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera()
	{
	}

	void InitializeCamera(const glm::vec3& pos, float fov, float aspect, float nearClip, float farClip)
	{
		this->m_Position = pos;
		this->m_Forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->m_Projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return m_Projection * glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
	}

	void MoveForward(float amt)
	{
		m_Position += m_Forward * amt;
	}

	void MoveRight(float amt)
	{
		m_Position += glm::cross(m_Up, m_Forward) * amt;
	}

	void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(m_Up, m_Forward));

		m_Forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(m_Forward, 0.0)));
		m_Up = glm::normalize(glm::cross(m_Forward, right));
	}

	void RotateY(float angle)
	{
		static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, UP);

		m_Forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_Forward, 0.0)));
		m_Up = glm::vec3(glm::normalize(rotation * glm::vec4(m_Up, 0.0)));
	}

protected:
private:
	glm::mat4 m_Projection;
	glm::vec3 m_Position;
	glm::vec3 m_Forward;
	glm::vec3 m_Up;
};


