
#define FUSE_USE_VERSION 26

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <unistd.h>
#include <fuse.h>
#include <limits.h>

//iptc

#include <libiptcdata/iptc-data.h>

char *psk_rootdir;
static const char *keyword_path = "/keywords";
static const char *subjects_path = "/subjects";
char keywords_array[100][PATH_MAX];
char subjects_array[100][PATH_MAX];
int ikeywords = 0, isubjects = 0;

static void file_pathTranslation(const char* path, char fullpath[PATH_MAX]){
	strcpy(fullpath, psk_rootdir);
    if (fullpath[strlen(fullpath)-1]!='/') {
        strcat(fullpath, "/");
    }
	strcat(fullpath, path);
}

void findDirectory(char *directory, const char *str){
	strcpy(directory,str+1);
	directory[8] = '\0';
}

static void pathTranslation(const char* path, char fullpath[PATH_MAX]){
	
    strcpy(fullpath,psk_rootdir);
    if (fullpath[strlen(fullpath)-1]=='/') {
        fullpath[strlen(fullpath)-1]='\0';
    }
    strcat(fullpath,path);

}

static int IsJpgFile(const char *str){
	int slength = strlen(str);
	int jlength = strlen(".jpg");
	if(slength >= jlength){
		if(!strcmp(str + slength - jlength, ".jpg")) 
			return 1;
	}
	return 0;
}

static void addToKeywords(char *str){
	if(ikeywords < 100){
		strcpy(keywords_array[ikeywords],str);
		ikeywords++;
	}
}

static void addToSubjects(char *str){
	if(isubjects < 100){
		strcpy(subjects_array[isubjects],str);
		isubjects++;
	}
}

static int IsKeyword(char *str){
	int i;
	for(i=0;i<ikeywords;i++){
		if (strcmp(str, keywords_array[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

static int IsSubject(char *str){
	int i;
	for(i=0;i<isubjects;i++){
		if (strcmp(str, subjects_array[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

static int findFileName(const char *str){
	char *a;
	a = str+strlen(str)-1;
	int index = strlen(str);
	while(*a!='/'){
		index --;
		a--;
	}
	return index;
}

static void findTag(char *tag, const char *str){
	strcpy(tag,str+10);
	int index = findFileName(tag);
	tag[index-1] = '\0';
}

static void updateArrays(){
	DIR *dp;
	struct dirent *de;
	char filename[PATH_MAX];
	dp = opendir(psk_rootdir);
	IptcData * d;
	IptcDataSet * e;
	char buffer[256];
	int i;

	while((de = readdir(dp)) != NULL) {
		if(IsJpgFile(de->d_name)){
			file_pathTranslation(de->d_name, filename);			
			d = iptc_data_new_from_jpeg (filename);
			if(!d) return 0;
			
			for (i=0; i < d->count; i++) {
				e = d->datasets[i];
				if(e->record == 2 && e->tag == 25){
					iptc_dataset_get_data (e, buffer, sizeof(buffer));
					if(!IsKeyword(buffer)){
						addToKeywords(buffer);
					}
				}
				if(e->record == 2 && e->tag == 12){
					iptc_dataset_get_data (e, buffer, sizeof(buffer));
					if(!IsSubject(buffer)){
						addToSubjects(buffer);
					}
				}
			}
		}
	}

	closedir(dp);
}

/****************
 *Fuse Callbacks*
 ****************/
 

static int psk_getattr(const char *path, struct stat *statbuf)
{   
    int path_length = strlen(path);
    
	int length_keyword = strlen(keyword_path)+1;
	int length_subject = strlen(subjects_path)+1;

    memset(statbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        statbuf->st_mode = S_IFDIR | 0755;
        statbuf->st_nlink = 4;
    }
    else if (strcmp(path, keyword_path) == 0) {
        statbuf->st_mode = S_IFDIR | 0755;
        statbuf->st_nlink = 2+ikeywords;
    }
    else if (strcmp(path, subjects_path) == 0) {
        statbuf->st_mode = S_IFDIR | 0755;
        statbuf->st_nlink = 3+isubjects;
    }
	else if(path_length > length_keyword && IsKeyword(path+length_keyword)){
		statbuf->st_mode = S_IFDIR | 0755;
		statbuf->st_nlink = 2;
	}
	else if(path_length > length_subject && IsSubject(path+length_subject)){
		statbuf->st_mode = S_IFDIR | 0755;
		statbuf->st_nlink = 2;
	}
	else if(IsJpgFile(path)){
		IptcData * d;
		IptcDataSet * e;
		char buffer[256];
		char directory_ks[256];
		char tag_ks[256];
		int i;
		int res = 0;
		char directory_path[PATH_MAX];
		int index = findFileName(path);
		findDirectory(directory_ks, path);
		findTag(tag_ks, path);
		file_pathTranslation(path+index,directory_path);
		d = iptc_data_new_from_jpeg (directory_path);
		if(!d) return 0;
		if(strcmp(directory_ks,"keywords")==0){
			for (i=0; i < d->count; i++) {
				e = d->datasets[i];
				if(e->record == 2 && e->tag == 25){
					iptc_dataset_get_data (e, buffer, sizeof(buffer));
					if(strcmp(buffer, tag_ks)==0){
						res = lstat(directory_path, statbuf);
						
						if(res == -1) {
							return -errno;
						}
					}
				}
			}			
		}
		if(strcmp(directory_ks,"subjects")==0){
			for (i=0; i < d->count; i++) {
				e = d->datasets[i];
				if(e->record == 2 && e->tag == 12){
					iptc_dataset_get_data (e, buffer, sizeof(buffer));
					if(strcmp(buffer, tag_ks)==0){
						res = lstat(directory_path, statbuf);
						
						if(res == -1) {
							return -errno;
						}
					}
				}
			}			
		}
	}
	else{
		return -ENOENT;
	}

    return 0;
}

static int psk_readdir(const char *path, void *buf, fuse_fill_dir_t filler,off_t offset, struct fuse_file_info *fi)
{
	updateArrays();
	int i;
	(void) fi;
	(void) offset;
	int path_length = strlen(path);
	
	if (strcmp(path, "/") == 0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		filler(buf, "keywords", NULL, 0);
		filler(buf, "subjects", NULL, 0);
	}
	else if(strcmp(path, keyword_path)==0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		for(i=0;i<ikeywords;i++){
			if (filler(buf, keywords_array[i], NULL, 0))
				break;
		}
	}
	else if(strcmp(path, subjects_path)==0){
		filler(buf, ".", NULL, 0);
		filler(buf, "..", NULL, 0);
		for(i=0;i<isubjects;i++){
			if (filler(buf, subjects_array[i], NULL, 0))
				break;
		}
	}
	else if (path_length > 10 && IsKeyword(path+10)){
		char keywordtoget[256];
		strcpy(keywordtoget, path+10);
		DIR *dp;
		struct dirent *de;
		char filename[PATH_MAX];
		IptcData * d;
		IptcDataSet * e;
		char buffer[256];
		int i;
		
		dp = opendir(psk_rootdir);
		
		while((de = readdir(dp)) != NULL) {
			if(IsJpgFile(de->d_name)){
				file_pathTranslation(de->d_name, filename);			
				d = iptc_data_new_from_jpeg (filename);
				if(!d) return 0;
				for (i=0; i < d->count; i++) {
					e = d->datasets[i];
					if(e->record == 2 && e->tag == 25){
						iptc_dataset_get_data (e, buffer, sizeof(buffer));
						if(strcmp(buffer, keywordtoget) == 0){
							if (filler(buf, de->d_name, NULL, 0))
								break;
						}
					}
				}
			}
		}
	}
	else if (path_length > 10 && IsSubject(path+10)){
		char subjecttoget[256];
		strcpy(subjecttoget, path+10);
		DIR *dp;
		struct dirent *de;
		char filename[PATH_MAX];
		IptcData * d;
		IptcDataSet * e;
		char buffer[256];
		int i;
		
		dp = opendir(psk_rootdir);
		
		while((de = readdir(dp)) != NULL) {
			if(IsJpgFile(de->d_name)){
				file_pathTranslation(de->d_name, filename);			
				d = iptc_data_new_from_jpeg (filename);
				if(!d) return 0;
				for (i=0; i < d->count; i++) {
					e = d->datasets[i];
					if(e->record == 2 && e->tag == 12){
						iptc_dataset_get_data (e, buffer, sizeof(buffer));
						if(strcmp(buffer, subjecttoget) == 0){
							if (filler(buf, de->d_name, NULL, 0))
								break;
						}
					}
				}
			}
		}
	}
	else{
		return -ENOENT;
	}

    return 0;
}

static int psk_open(const char *path, struct fuse_file_info *finfo)
{
	if(IsJpgFile(path)){
		int res;

		int flags = finfo->flags;
		char directory_path[PATH_MAX];
		int index = findFileName(path);

		file_pathTranslation(path+index, directory_path);

		res = open(directory_path, flags);

		if(res == -1) {
			return -errno;
		}
		close(res);
	}
    return 0;
}

static int psk_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *finfo)
{
	int res=0;
	if(IsJpgFile(path)){
		int fd;
		(void)finfo;
		char directory_path[PATH_MAX];
		int index = findFileName(path);

		file_pathTranslation(path+index, directory_path);
		fd = open(directory_path, O_RDONLY);
		if(fd == -1) {
			res = -errno;
			return res;
		}
		res = pread(fd, buf, size, offset);

		if(res == -1) {
			res = -errno;
		}
		close(fd);
	}
	return res;
}

static int psk_create(const char *path, mode_t mode, struct fuse_file_info *fi){
	char tag_file[256];
	findTag(tag_file,path);
	if(strncmp(keyword_path, path, 10)==0){
		IptcData *d;
		IptcDataSet * ds;
		IptcRecord record;
		IptcTag tag;
		char directory_path[PATH_MAX];

		int index = findFileName(path);
		
		file_pathTranslation(path+index,directory_path);

		d = iptc_data_new_from_jpeg (directory_path);
		
		if(!d){
			return 0;
		}			
		
		if (iptc_tag_find_by_name ("Keywords", &record, &tag) < 0) {
			return 0;
		}

		ds = iptc_data_get_dataset (d, record, tag);
		if (!ds) {
			return 0;
		}
		iptc_dataset_set_data(ds, tag_file, strlen(tag_file), IPTC_DONT_VALIDATE);
		iptc_dataset_unref (ds);
	}
	if(strncmp(subjects_path, path, 10)==0){
		IptcData *d;
		IptcDataSet * ds;
		IptcRecord record;
		IptcTag tag;
		char directory_path[PATH_MAX];

		int index = findFileName(path);
		
		file_pathTranslation(path+index,directory_path);

		d = iptc_data_new_from_jpeg (directory_path);
		
		if(!d){
			return 0;
		}			
		
		if (iptc_tag_find_by_name ("SubjectRef", &record, &tag) < 0) {
			return 0;
		}

		ds = iptc_data_get_dataset (d, record, tag);
		if (!ds) {
			return 0;
		}
		iptc_dataset_set_data(ds, tag_file, strlen(tag_file), IPTC_DONT_VALIDATE);
		iptc_dataset_unref (ds);
	}
	return 0;
}

static int psk_unlink(const char *path)
{
	int retval;
	/*
	int index = findFileName(path);
	char filename[PATH_MAX];
	IptcDataSet * ds;
	*/

	printf("---unlink---\n");

	// find the tag value 
	char tag_value[256];
	findTag(tag_value,path);
	printf("tag value: %s\n", tag_value);
	printf("path: %s\n", path);
	printf("keyword path: %s\n", keyword_path);
			
	IptcData *d;
	IptcDataSet *ds;		//contains tag type (ds->tag) and tag value(ds->data)
	IptcRecord record;		//enum
	IptcTag tag;			//enum
	char input_filename[PATH_MAX];
	int index = findFileName(path);
	
	file_pathTranslation(path+index,input_filename);

	//
	printf("translated path: %s\n", input_filename);

	d = iptc_data_new_from_jpeg (input_filename);
	
	if(!d){
		return 0;
	}			
	
	// datayı ekrana bas
	iptc_data_dump(d,0);

	if(strncmp(keyword_path, path, 9)==0)
	{
		printf("tag type is keywords!!\n");
		if (iptc_tag_find_by_name ("Keywords", &record, &tag) < 0) {
			return 0;
		}
	}

	if(strncmp(subjects_path, path, 9)==0)
	{
		printf("tag type is subjects!!\n");
		if (iptc_tag_find_by_name ("SubjectRef", &record, &tag) < 0) {
			return 0;
		}
	}

	//ds = iptc_data_get_dataset (d, record, tag);		
	//if (!ds) {
	//	return 0;
	//}
	ds = NULL;		

	ds = iptc_data_get_next_dataset(d, ds, record, tag);	//iptc_data_get_next_dataset gets first dataset when ds is null initially
	
	// iterate datasets until finding the right one
	while(strcmp(tag_value, ds->data) != 0)
	{
		ds = iptc_data_get_next_dataset(d, ds, record, tag);
		if(ds == NULL)
			return 0;
	}

	printf("dataset->data: %s\n", ds->data);

	retval = iptc_data_remove_dataset (d, ds);		// return 0 if success
	iptc_dataset_unref (ds);

	// datayı ekrana bas
	iptc_data_dump(d,0);

	
	/*
	// create a temp file name
	char temp_filename[PATH_MAX];
	strcpy(temp_filename, input_filename);
	*temp_filename = strtok(temp_filename, ".");
	strncat(temp_filename,"_temp.jpg",9);

	printf("temp_filename: %s\n", temp_filename);
	printf("input_filename: %s\n", input_filename);
	*/

	///// 	section website
	
	unsigned char * iptc_buf = NULL;
	unsigned char outbuf[256*256];
	//unsigned char buf[256*256];
	int ps3_len, iptc_off, iptc_len;
	FILE *infile, *outfile;
	char temp_filename[strlen(input_filename)+8];
	//int v;

	iptc_data_sort (d);

	// save the modified data to iptc_buf
	if (iptc_data_save(d, &iptc_buf, &iptc_len) < 0) {
		fprintf (stderr, "Failed to generate IPTC bytestream\n");
		return 1;
	}

	// create new ps3 header from scract (into outbuf)
	ps3_len = iptc_jpeg_ps3_save_iptc (NULL, ps3_len, iptc_buf, iptc_len, outbuf, sizeof(outbuf));
	iptc_data_free_buf (d, iptc_buf);
	if (ps3_len < 0) {
		fprintf (stderr, "Failed to generate PS3 header\n");
		return 1;
	}

	infile = fopen(input_filename, "r");
	if (!infile) {
		fprintf (stderr, "Can't reopen input file: %s\n", input_filename);
		return 1;
	}

	sprintf (temp_filename, "%s.%d", input_filename, getpid());
	outfile = fopen(temp_filename, "w");
	if (!outfile) {
		fprintf (stderr, "Can't open temp file\n");
		return 1;
	}

	// take old file, remove existing header, add new ps3 header
	retval = iptc_jpeg_save_with_ps3 (infile, outfile, outbuf, ps3_len);
	fclose (infile);
	fclose (outfile);
	if (retval < 0) {
		unlink (temp_filename);
		fprintf (stderr, "Failed to save image\n");
		return 1;
	}

	if (rename (temp_filename, input_filename) < 0) {
		fprintf (stderr, "Failed to save image\n");
		unlink (temp_filename);
		return 1;
	}
	fprintf (stderr, "Image saved\n");
	
	/////////////////////////////////////////// endsection
	

	///////////////////// section tuğrul
	/*
	//IptcData * d;
	FILE * infile, *outfile;
	int ps3_len, iptc_off, iptc_len;
	unsigned char buf[256*256];

	infile = fopen (input_filename, "r");
	if (!infile) {
		fprintf (stderr, "Error opening %s\n", input_filename);
		return 1;
	}

	ps3_len = iptc_jpeg_read_ps3 (infile, buf, sizeof(buf));
	fclose (infile);
	if (ps3_len < 0) {
		fprintf (stderr, "Error parsing JPEG file\n");
		return 1;
	}

	if (ps3_len == 0) {
		fprintf (stderr, "File contains no PS3 header\n");
		return 1;
	}

	iptc_off = iptc_jpeg_ps3_find_iptc (buf, ps3_len, &iptc_len);
	if (iptc_off < 0) {
		fprintf (stderr, "Error parsing PS3 header\n");
		return 1;
	}

	if (iptc_off == 0) {
		fprintf (stderr, "PS3 header contains no IPTC data\n");
		return 1;
	}

	d = iptc_data_new_from_data (buf + iptc_off, iptc_len);
	if (!d) {
		fprintf (stderr, "Error parsing IPTC data\n");
		return 1;
	}
	
	IptcDataSet * ds;
	IptcRecord record;
	IptcTag tag;

	if (iptc_tag_find_by_name (tag_type, &record, &tag) < 0) {
		fprintf (stderr, "Invalid tag name\n");
		return 1;
	}

	ds = iptc_dataset_new ();
	iptc_dataset_set_tag (ds, record, tag);
	iptc_dataset_set_data (ds, tag_v, 6, IPTC_DONT_VALIDATE);
	iptc_data_add_dataset (d, ds);
	iptc_dataset_unref (ds);
	
	unsigned char * iptc_buf = NULL;
	unsigned char outbuf[256*256];
	char tmpfile[strlen(filename)+8];
	int v;

	iptc_data_sort (d);

	if (iptc_data_save (d, &iptc_buf, &iptc_len) < 0) {
		fprintf (stderr, "Failed to generate IPTC bytestream\n");
		return 1;
	}
	ps3_len = iptc_jpeg_ps3_save_iptc (buf, ps3_len,
			iptc_buf, iptc_len, outbuf, sizeof(outbuf));
	iptc_data_free_buf (d, iptc_buf);
	if (ps3_len < 0) {
		fprintf (stderr, "Failed to generate PS3 header\n");
		return 1;
	}

	infile = fopen (filename, "r");
	if (!infile) {
		fprintf (stderr, "Can't reopen input file\n");
		return 1;
	}
	sprintf (tmpfile, "%s.%d", filename, getpid());
	outfile = fopen (tmpfile, "w");
	if (!outfile) {
		fprintf (stderr, "Can't open temporary file for writing\n");
		return 1;
	}

	v = iptc_jpeg_save_with_ps3 (infile, outfile, outbuf, ps3_len);
	fclose (infile);
	fclose (outfile);
	if (v < 0) {
		unlink (tmpfile);
		fprintf (stderr, "Failed to save image\n");
		return 1;
	}

	if (rename (tmpfile, filename) < 0) {
		fprintf (stderr, "Failed to save image\n");
		unlink (tmpfile);
		return 1;
	}
	fprintf (stderr, "Image saved\n");
	return 0;
	*/
	////////////////////////////////// endsection

	


	return retval;
}

struct fuse_operations psk_oper = {
    .getattr     = psk_getattr,
    .create		 = psk_create,
    .readdir     = psk_readdir,
    .open        = psk_open,
    .read		 = psk_read,
    .unlink      = psk_unlink,
};

int main(int argc, char *argv[])
{
		psk_rootdir = realpath(argv[argc-2], NULL);
		argv[argc-2] = argv[argc-1];
		argv[argc-1] = NULL;
		argc--;
		fuse_main(argc, argv, &psk_oper, NULL);
		
		return 0;
}
