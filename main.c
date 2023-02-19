#include "assmbler.h"

DEFINE ERROR 1
DEFINE SIZE_MAX

struct s_label {
  char    *name;
  char    *bytecode;
  t_instructs *list
  s_label *next;
} t_label;
**hashtable = sizeof(t_label *) * n_labels;

int	save_file(main struct, champion file)
{
	int	line;
	int	i;

	i = 0;
	line = 1;

	/* either malloc or check for max line */
	while line > 0
	{
		data->file[i] = get_next_line(champion file);
		i++;
	}
	if data->file
		return (0);
	else
		return (ERROR);
}

int	save_input(main struct)
{
	if data->file[i] == LABEL
		label->name = data->file[i];
	if data->file[i] == instructions 
		label->instruct->list = data->file[i];
}
	


int	validate_file(main struct)
{
	if valid_input(data->file) != 1
		save_input;
}

int	main(champion file)
{
	takes champion as arg;
	if no champion
		exit;
	else champion exist	
	{
		if save_file == 1
			error_exit(main struct);
		if validate_file == 1
			error_exit(main struct);
		if translate_binaryi == 1
			error_exit(main struct);
	}
	return (0);
}


		
		
