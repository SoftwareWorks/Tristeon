﻿#pragma once
#include <string>
#include <map>
#include "Image.h"

namespace Tristeon
{
	namespace Data
	{
		/**
		* \brief The image batch is used to load in image files and store them until they're needed.
		* The image batch defines functionality for loading, unloading and getting image data
		 */
		class ImageBatch
		{
		public:
			/**
			 * \brief GetImage loads an image or returns a cached image
			 * \param path The path to the image file
			 * \return Returns the loaded image
			 */
			static Image getImage(std::string path);

			/**
			 * \brief Loads in an image and cashes it
			 * \param path The path of the image file
			 */
			static bool load(std::string path);
			/**
			 * \brief Unloads and frees the image from cache. Use with caution.
			 * \param path The path of the image file
			 */
			static void unload(std::string path);

		private:
			/**
			 * \brief The cached images
			 */
			static std::map<std::string, Image> cachedImages;
			/**
			 * \brief Unloads and frees all the images from the cache.
			 */
			static void unloadAll();
		};
	}
}
