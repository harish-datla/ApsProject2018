# APS_Project_2018
        The code has both cpp files and python files. Cpp files are for functionality of respective trees while python files are for graph plotting. After the executables of respective cpp files have been formed, you need to follow the following procedure.

        Run the .exe file of test_case_generator , this will create two text files one is random_seq.txt which has random numbers and sorted_seq which has sorted numbers.

        Once the text files have been created you can proceed to test the code by the following commands.

        To test randomized binary search tree , type ./randomized_bst txtfile, where txtfile can be random_seq.txt or sorted_seq.txt depending on your choice, so the commands look like.

    ./randomized_bst random_seq.txt

    ./randomized_bst sorted_seq.txt

    for balanced trees:

    ./avl_tree random_seq.txt

    ./avl_tree sorted_seq.txt

    ./rbtree random_seq.txt

    ./rbtree sorted_seq.txt

        From this you will have some .csv files generated which will help us in plotting graphs. To do the following you need to have the following installed in your system.

        plotly (to install click here ) ,     pandas (to install click here ) ,

        if these commands are not working for you try replacing pip3 in the commands instead of pip.

        Its also advisable to have a user account with plotly to be able to see the graphs for yourselves(refer above link), Also you have to change the following line in all .py with your credentials to be able to see the graphs in your profile.

       plotly.tools.set_credentials_file(username='xyz', api_key='k1278983977363746374637').

       once you are done run the following commands in your shell to be able to view the graphs

    python rotate_insert_height.py

    python rotate_delete_height.py

    python avl_tree_height.py

    python rbtree_height.py

    python operations_comparison.py

    python trees_comparison.py

