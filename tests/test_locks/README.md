Test the dynamic detection of changes in a file containing parameters

In a first terminal, run

    ./write_parameters
    
In  a second terminal, run

    ./read_params
    
You should observe that every time write_parameters modifies params.toml, read_params reads the updated version.

Good.

No we would like to do the same thing with a python producer in lieu of write_parameters

    python slider.py
    
Problem is: it sometimes crashes, as if the lock was not working

    
