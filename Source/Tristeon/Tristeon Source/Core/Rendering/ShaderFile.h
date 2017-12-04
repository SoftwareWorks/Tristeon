﻿#pragma once
#include <string>
#include "RenderAPI.h"
#include "Editor/Serializable.h"
#include "Editor/TypeRegister.h"

namespace Tristeon
{
	namespace Core
	{
		namespace Rendering
		{
			/**
			 * \brief Describes the type of shader, used to request a shader file path
			 */
			enum ShaderType
			{
				/**
				 * \brief The vertex shader
				 */
				ST_Vertex,
				/**
				 * \brief The fragment shader
				 */
				ST_Fragment
			};

			enum DataType
			{
				DT_Image,
				DT_Color,
				DT_Float,
				DT_Vector3
			};

			/**
			 * \brief ShaderFile is a class that is used to describe a shader's path and its properties
			 */
			class ShaderFile : public Serializable
			{
			public:
				/**
				 * \brief Creates a new shaderfile with empty data. Mainly used for serialization
				 */
				ShaderFile();
				/**
				 * \brief Creates a new shaderfile with the given data. Used for custom non-serialized shader files
				 * \param name The name ID of the shader
				 * \param directory The directory of the shader files
				 * \param vertexName The name of the vertex shader
				 * \param fragmentName The name of the fragment shader
				 */
				ShaderFile(std::string name, std::string directory, std::string vertexName, std::string fragmentName);

				/**
				 * \brief Gets the path to this shaderfile based on the given api and shader type
				 * \param api The active rendering API
				 * \param type The type of shader (vertex/fragment)
				 * \return Returns a string describing the exact filepath
				 */
				std::string getPath(RenderAPI api, ShaderType type) const;
				
				/**
				 * \return Gets the name id of the shaderfile 
				 */
				std::string getNameID() const { return nameID; }
			private:
				/**
				 * \brief ShaderFiles can be identified by their nameID
				 */
				std::string nameID;
				/**
				 * \brief The directory of the shader
				 */
				std::string directory;
				/**
				 * \brief The name of the vertex shader file
				 */
				std::string vertexName;
				/**
				 * \brief The name of the fragment shader file
				 */
				std::string fragmentName;

				/**
				 * \brief Generates a json object containing the data of this shader file
				 * \return Returns the json object
				 */
				nlohmann::json serialize() override;
				/**
				 * \brief Deserializes the given json object into this object's data
				 * \param json The json containing the serialized data
				 */
				void deserialize(nlohmann::json json) override;
				
				std::map<std::string, DataType> properties;

				REGISTER_TYPE_H(ShaderFile)
			};
		}
	}
}
