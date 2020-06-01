#! /bin/bash

pexec() { echo "\$ $*" ; "$@" ; }

# put

# var

pexec sed -i 's/ncmpi_put_var_int/HDF5_PUT_VAR_INT/' $1
pexec sed -i 's/ncmpi_put_var_double/HDF5_PUT_VAR_DOUBLE/' $1
pexec sed -i 's/ncmpi_put_var_float/HDF5_PUT_VAR_FLOAT/' $1
pexec sed -i 's/ncmpi_put_var_text/HDF5_PUT_VAR_TEXT/' $1

pexec sed -i 's/ncmpi_put_var_int_all/HDF5_PUT_VAR_INT_ALL/' $1
pexec sed -i 's/ncmpi_put_var_double_all/HDF5_PUT_VAR_DOUBLE_ALL/' $1
pexec sed -i 's/ncmpi_put_var_float_all/HDF5_PUT_VAR_FLOAT_ALL/' $1
pexec sed -i 's/ncmpi_put_var_text_all/HDF5_PUT_VAR_TEXT_ALL/' $1

pexec sed -i 's/ncmpi_iput_var_int/HDF5_IPUT_VAR_INT/' $1
pexec sed -i 's/ncmpi_iput_var_double/HDF5_IPUT_VAR_DOUBLE/' $1
pexec sed -i 's/ncmpi_iput_var_float/HDF5_IPUT_VAR_FLOAT/' $1
pexec sed -i 's/ncmpi_iput_var_text/HDF5_IPUT_VAR_TEXT/' $1

# vara

pexec sed -i 's/ncmpi_put_vara_int/HDF5_PUT_VARA_INT/' $1
pexec sed -i 's/ncmpi_put_vara_double/HDF5_PUT_VARA_DOUBLE/' $1
pexec sed -i 's/ncmpi_put_vara_float/HDF5_PUT_VARA_FLOAT/' $1
pexec sed -i 's/ncmpi_put_vara_text/HDF5_PUT_VARA_TEXT/' $1

pexec sed -i 's/ncmpi_put_vara_int_all/HDF5_PUT_VARA_INT_ALL/' $1
pexec sed -i 's/ncmpi_put_vara_double_all/HDF5_PUT_VARA_DOUBLE_ALL/' $1
pexec sed -i 's/ncmpi_put_vara_float_all/HDF5_PUT_VARA_FLOAT_ALL/' $1
pexec sed -i 's/ncmpi_put_vara_text_all/HDF5_PUT_VARA_TEXT_ALL/' $1

pexec sed -i 's/ncmpi_iput_vara_int/HDF5_IPUT_VARA_INT/' $1
pexec sed -i 's/ncmpi_iput_vara_double/HDF5_IPUT_VARA_DOUBLE/' $1
pexec sed -i 's/ncmpi_iput_vara_float/HDF5_IPUT_VARA_FLOAT/' $1
pexec sed -i 's/ncmpi_iput_vara_text/HDF5_IPUT_VARA_TEXT/' $1

# var1

pexec sed -i 's/ncmpi_put_var1_int/HDF5_PUT_VAR1_INT/' $1
pexec sed -i 's/ncmpi_put_var1_double/HDF5_PUT_VAR1_DOUBLE/' $1
pexec sed -i 's/ncmpi_put_var1_float/HDF5_PUT_VAR1_FLOAT/' $1
pexec sed -i 's/ncmpi_put_var1_text/HDF5_PUT_VAR1_TEXT/' $1

pexec sed -i 's/ncmpi_put_var1_int_all/HDF5_PUT_VAR1_INT_ALL/' $1
pexec sed -i 's/ncmpi_put_var1_double_all/HDF5_PUT_VAR1_DOUBLE_ALL/' $1
pexec sed -i 's/ncmpi_put_var1_float_all/HDF5_PUT_VAR1_FLOAT_ALL/' $1
pexec sed -i 's/ncmpi_put_var1_text_all/HDF5_PUT_VAR1_TEXT_ALL/' $1

pexec sed -i 's/ncmpi_iput_var1_int/HDF5_IPUT_VAR1_INT/' $1
pexec sed -i 's/ncmpi_iput_var1_double/HDF5_IPUT_VAR1_DOUBLE/' $1
pexec sed -i 's/ncmpi_iput_var1_float/HDF5_IPUT_VAR1_FLOAT/' $1
pexec sed -i 's/ncmpi_iput_var1_text/HDF5_IPUT_VAR1_TEXT/' $1

# varn

pexec sed -i 's/ncmpi_put_varn/HDF5_PUT_VARN/' $1
pexec sed -i 's/ncmpi_iput_varn/HDF5_IPUT_VARN/' $1

# get

# var

pexec sed -i 's/ncmpi_get_var_int/HDF5_GET_VAR_INT/' $1
pexec sed -i 's/ncmpi_get_var_double/HDF5_GET_VAR_DOUBLE/' $1
pexec sed -i 's/ncmpi_get_var_float/HDF5_GET_VAR_FLOAT/' $1
pexec sed -i 's/ncmpi_get_var_text/HDF5_GET_VAR_TEXT/' $1

pexec sed -i 's/ncmpi_get_var_int_all/HDF5_GET_VAR_INT_ALL/' $1
pexec sed -i 's/ncmpi_get_var_double_all/HDF5_GET_VAR_DOUBLE_ALL/' $1
pexec sed -i 's/ncmpi_get_var_float_all/HDF5_GET_VAR_FLOAT_ALL/' $1
pexec sed -i 's/ncmpi_get_var_text_all/HDF5_GET_VAR_TEXT_ALL/' $1

pexec sed -i 's/ncmpi_iget_var_int/HDF5_IGET_VAR_INT/' $1
pexec sed -i 's/ncmpi_iget_var_double/HDF5_IGET_VAR_DOUBLE/' $1
pexec sed -i 's/ncmpi_iget_var_float/HDF5_IGET_VAR_FLOAT/' $1
pexec sed -i 's/ncmpi_iget_var_text/HDF5_IGET_VAR_TEXT/' $1

# vara

pexec sed -i 's/ncmpi_get_vara_int/HDF5_GET_VARA_INT/' $1
pexec sed -i 's/ncmpi_get_vara_double/HDF5_GET_VARA_DOUBLE/' $1
pexec sed -i 's/ncmpi_get_vara_float/HDF5_GET_VARA_FLOAT/' $1
pexec sed -i 's/ncmpi_get_vara_text/HDF5_GET_VARA_TEXT/' $1

pexec sed -i 's/ncmpi_get_vara_int_all/HDF5_GET_VARA_INT_ALL/' $1
pexec sed -i 's/ncmpi_get_vara_double_all/HDF5_GET_VARA_DOUBLE_ALL/' $1
pexec sed -i 's/ncmpi_get_vara_float_all/HDF5_GET_VARA_FLOAT_ALL/' $1
pexec sed -i 's/ncmpi_get_vara_text_all/HDF5_GET_VARA_TEXT_ALL/' $1

pexec sed -i 's/ncmpi_iget_vara_int/HDF5_IGET_VARA_INT/' $1
pexec sed -i 's/ncmpi_iget_vara_double/HDF5_IGET_VARA_DOUBLE/' $1
pexec sed -i 's/ncmpi_iget_vara_float/HDF5_IGET_VARA_FLOAT/' $1
pexec sed -i 's/ncmpi_iget_vara_text/HDF5_IGET_VARA_TEXT/' $1

# var1

pexec sed -i 's/ncmpi_get_var1_int/HDF5_GET_VAR1_INT/' $1
pexec sed -i 's/ncmpi_get_var1_double/HDF5_GET_VAR1_DOUBLE/' $1
pexec sed -i 's/ncmpi_get_var1_float/HDF5_GET_VAR1_FLOAT/' $1
pexec sed -i 's/ncmpi_get_var1_text/HDF5_GET_VAR1_TEXT/' $1

pexec sed -i 's/ncmpi_get_var1_int_all/HDF5_GET_VAR1_INT_ALL/' $1
pexec sed -i 's/ncmpi_get_var1_double_all/HDF5_GET_VAR1_DOUBLE_ALL/' $1
pexec sed -i 's/ncmpi_get_var1_float_all/HDF5_GET_VAR1_FLOAT_ALL/' $1
pexec sed -i 's/ncmpi_get_var1_text_all/HDF5_GET_VAR1_TEXT_ALL/' $1

pexec sed -i 's/ncmpi_iget_var1_int/HDF5_IGET_VAR1_INT/' $1
pexec sed -i 's/ncmpi_iget_var1_double/HDF5_IGET_VAR1_DOUBLE/' $1
pexec sed -i 's/ncmpi_iget_var1_float/HDF5_IGET_VAR1_FLOAT/' $1
pexec sed -i 's/ncmpi_iget_var1_text/HDF5_IGET_VAR1_TEXT/' $1

# varn

pexec sed -i 's/ncmpi_get_varn/HDF5_GET_VARN/' $1
pexec sed -i 's/ncmpi_iget_varn/HDF5_IGET_VARN/' $1

# attr

pexec sed -i 's/ncmpi_put_att_text/HDF5_PUT_ATT_TEXT/' $1
pexec sed -i 's/ncmpi_get_att_text/HDF5_GET_ATT_TEXT/' $1

pexec sed -i 's/ncmpi_put_att_int/HDF5_PUT_ATT_INT/' $1
pexec sed -i 's/ncmpi_get_att_int/HDF5_GET_ATT_INT/' $1

pexec sed -i 's/ncmpi_put_att_float/HDF5_PUT_ATT_FLOAT/' $1
pexec sed -i 's/ncmpi_get_att_float/HDF5_GET_ATT_FLOAT/' $1

# misc

pexec sed -i 's/ncmpi_def_dim/hdf5_def_dim/' $1
pexec sed -i 's/ncmpi_inq_dimid/hdf5_inq_dimid/' $1
pexec sed -i 's/ncmpi_inq_dimlen/hdf5_inq_dimlen/' $1

pexec sed -i 's/ncmpi_def_var/hdf5_def_var/' $1
pexec sed -i 's/ncmpi_inq_varid/hdf5_inq_varid/' $1

pexec sed -i 's/ncmpi_enddef/HDF5_NOP1/' $1

pexec sed -i 's/ncmpi_wait_all/HDF5_WAIT_ALL/' $1

pexec sed -i 's/ncmpi_inq_file_info/HDF5_INQ_FILE_INFO/' $1

pexec sed -i 's/ncmpi_inq_put_size/HDF5_INQ_PUT_SIZE/' $1
pexec sed -i 's/ncmpi_inq_put_size/HDF5_INQ_GET_SIZE/' $1

pexec sed -i 's/ncmpi_inq_malloc_size/HDF5_NOP1/' $1
pexec sed -i 's/ncmpi_inq_malloc_max_size/HDF5_NOP1/' $1


