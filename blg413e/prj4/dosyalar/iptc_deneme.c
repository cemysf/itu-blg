//#include <IptcData.h>
#include <libiptcdata/iptc-data.h>
#include <stdio.h>

int main(){
	IptcData * d;
	char * filename = "dphoto.jpg";

	d = iptc_data_new_from_jpeg(filename);
	if (!d) {
		fprintf (stderr, "Error reading IPTC data\n");
		return 1;
	}
	int i;
//~ 
//~ printf("%6.6s %-20.20s %-9.9s %6s  %s\n", "Tag", "Name", "Type",
		//~ "Size", "Value");
//~ printf(" ----- -------------------- --------- ------  -----\n");
//~ 
//~ for (i=0; i < d->count; i++) {
	//~ IptcDataSet * e = d->datasets[i];
	//~ char buf[256];
//~ 
	//~ printf("%2d:%03d %-20.20s %-9.9s %6d  ",
			//~ e->record, e->tag,
			//~ iptc_tag_get_title (e->record, e->tag),
			//~ iptc_format_get_name (iptc_dataset_get_format (e)),
			//~ e->size);
	//~ switch (iptc_dataset_get_format (e)) {
		//~ case IPTC_FORMAT_BYTE:
		//~ case IPTC_FORMAT_SHORT:
		//~ case IPTC_FORMAT_LONG:
			//~ printf("%d\n", iptc_dataset_get_value (e));
			//~ break;
		//~ case IPTC_FORMAT_BINARY:
			//~ iptc_dataset_get_as_str (e, buf, sizeof(buf));
			//~ printf("%s\n", buf);
			//~ break;
		//~ default:
			//~ iptc_dataset_get_data (e, buf, sizeof(buf));
			//~ printf("%s\n", buf);
			//~ break;
	//~ }
//~ }

return 0;
}
