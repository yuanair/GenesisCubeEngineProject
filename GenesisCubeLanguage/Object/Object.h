#pragma once
#include <map>
#include <string>

namespace GCL
{

	namespace Object
	{

		class Object
		{
		public:

			enum Type
			{
				Object_Error = 0,
				Object_Integer,
				Object_Float,
				Object_Bool,
				Object_Char
			};

		public:

			Object() : Object(Object_Error) {}
			virtual ~Object() {}

			Object(Type type) : type(type) {}

		public:

			Type GetType() const;

			std::string ToTypeString() const;

			virtual std::string ToString() = 0;

		protected:

			Type type;

		private:

			static std::map<Type, std::string> names;

		};

	}
}