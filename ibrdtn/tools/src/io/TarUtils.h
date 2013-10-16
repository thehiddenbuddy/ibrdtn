/*
 * TarUtils.h
 *
 * Copyright (C) 2013 IBR, TU Braunschweig
 *
 * Written-by: David Goltzsche <goltzsch@ibr.cs.tu-bs.de>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *  Created on: Sep 16, 2013
 */

#ifndef TARUTILS_H_
#define TARUTILS_H_
#include "config.h"
#ifdef HAVE_LIBARCHIVE
#include "FATFile.h"
#include "ObservedFile.h"

#include <ibrcommon/data/BLOB.h>
#include <archive.h>
#include <archive_entry.h>
#include <fcntl.h>

#ifdef HAVE_LIBTFFS
extern "C"
{
#include <tffs.h>
}
#endif
#endif
struct tarfile
{
	const char *filename;
	archive_entry *entry;
};
class TarUtils
{
public:
	TarUtils();
	virtual ~TarUtils();

	/**
	 * write tar archive to payload block, FATFile version
	 */
	static void write_tar_archive( ibrcommon::BLOB::Reference* blob, list<ObservedFile*> files_to_send );

	/*
	 * set path of vfat-image, "" if not on image
	 */
	static void set_img_path(std::string img_path);

	/*
	 * set path of outbox
	 */
	static void set_outbox_path(std::string outbox_path);


	/*
	 * read tar archive from payload block, write to file
	 */
	static void read_tar_archive( string extract_folder, ibrcommon::BLOB::Reference *blob );

private:
	static string rel_filename(string);
	static string dir_path(string);

	static std::string _img_path;
	static std::string _outbox_path;

	//tffs handles
#ifdef HAVE_LIBTFFS
	static tffs_handle_t htffs;
	static tdir_handle_t hdir;
	static tfile_handle_t hfile;
#endif
	static int ret;

	//CALLBACKS FOR LIBARCHIVE
	static int close_callback( struct archive *, void *blob_iostream );
	static ssize_t write_callback( struct archive *, void *blob_ptr, const void *buffer, size_t length );
	static int open_callback( struct archive *, void *blob_iostream );
	static ssize_t read_callback( struct archive *a, void *client_data, const void **buff );
};

#endif /* TARUTILS_H_ */
