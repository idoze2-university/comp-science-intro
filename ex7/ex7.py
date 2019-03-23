#Student Name: Ido Zeira
#Exercise: ex7
#Username: zeiraid
#ID: 322607177
import sys
import os

#####################################################
#function name: load_movie_to_actor                 #
#input: actor_to_movies (db)                        #
#output: loaded movie_to_actors                     #
#function: loads content from actor_to_movies to    #
#          movie_to_actors                          #
#####################################################
def load_movie_to_actor(actor_to_movies):
    movie_to_actors = dict()
    for actor,movies in actor_to_movies.items():
        for movie in movies:
            if movie not in movie_to_actors:
                movie_to_actors.setdefault(movie,set())
            movie_to_actors.get(movie).add(actor)
    return movie_to_actors


#####################################################
#function name: query_by_movies_and                 #
#input: movie_to_actors (db) and 2 movies           #
#output: result actor list                          #
#function: lists AND operation's result on actors   #
#          of both movies                           #
#####################################################
def query_by_movies_and(movie_to_actors,movie_1,movie_2):
    return [actor for actor in movie_to_actors[movie_1] if actor in movie_to_actors[movie_2]]
    


#####################################################
#function name: query_by_movies_or                  #
#input: movie_to_actors (db) and 2 movies           #
#output: result actor list                          #
#function: lists OR operation's result on actors    #
#          of both movies                           #
#####################################################
def query_by_movies_or(movie_to_actors,movie_1,movie_2):
    return list(movie_to_actors[movie_1].union(movie_to_actors[movie_2]))


#####################################################
#function name: query_by_movies_xor                 #
#input: movie_to_actors (db) and 2 movies           #
#output: result actor list                          #
#function: lists XOR operation's result on actors   #
#          of both movies                           #
#####################################################
def query_by_movies_xor(movie_to_actors,movie_1,movie_2):
    return list(movie_to_actors[movie_1].symmetric_difference(movie_to_actors[movie_2]))


#####################################################
#function name: query_by_movies                     #
#input: movie_to_actors (db)                        #
#output: None                                       #
#function: print an operation's result on actors   #
#          of both movies                           #
#####################################################
def query_by_movies(movie_to_actors):
    inp = input("Please select two movies and an operator(&,|,^) separated with \',\':\n")
    args = [arg.strip(" ") for arg in inp.split(',')]
    operator_to_func = {'&':query_by_movies_and,'|':query_by_movies_or,'^':query_by_movies_xor}
    if len(args)!=3 or args[0] not in movie_to_actors or args[1] not in movie_to_actors or args[2] not in operator_to_func:
        print("Error")
    else:
        matches = operator_to_func.get(args[2])(movie_to_actors,args[0],args[1])
        if(len(matches) == 0):
            print("There are no actors in this group")
        else:
            print(', '.join(sorted(matches)))


#####################################################
#function name: query_by_actors                     #
#input: actor_to_movies,movie_to_actors (db)        #
#output: None                                       #
#function: prints a list of co-starring actors of   # 
#          actor                                    #
#####################################################
def query_by_actors(actor_to_movies,movie_to_actors):
    actor_name = input("Please select an actor:\n").strip(" ")
    if actor_name not in actor_to_movies:
        print("Error")
        return
    co_actors = set()
    for movie in actor_to_movies[actor_name]:
        for actor in movie_to_actors[movie]:
            if actor != actor_name:
                co_actors.add(actor)
    if(len(co_actors)==0):
        print("There are no actors in this group")
    else:
        print(", ".join(sorted(co_actors)))
    return


#####################################################
#function name: new_movie                           #
#input: movie_to_actors (db)                        #
#output: updated movie_to_actors                    #
#function: inputs a movie and actors and inserts it #
#          To movie_to_actors                       #
#####################################################
def new_movie(movie_to_actors):
    inp = input("Please insert a new movie:\n")
    fields = list(field.strip("\n ") for field in inp.split(','))
    if len(fields) <2:
        print("Error")
        return movie_to_actors
    if fields[0] in movie_to_actors:
        movie_to_actors[fields[0]]= set(movie_to_actors[fields[0]]).union(set(f.strip(' ') for f in fields[1:]))
    else:
        movie_to_actors.setdefault(fields[0],[f.strip(' ') for f in fields[1:]])
    return movie_to_actors


#####################################################
#function name: update_actor_to_movies              #
#input: movie_to_actors (db)                        #
#output: updated actor_to_movies                    #
#function: syncs both databases                     #
#####################################################
def update_actor_to_movies(movie_to_actors,actor_to_movies):
    for movie,movie_actors in movie_to_actors.items():
        for actor in movie_actors:
            if actor not in actor_to_movies:
                actor_to_movies.setdefault(actor,set())
            else:
                actor_to_movies[actor].add(movie)
    return actor_to_movies


#####################################################
#function name: save_and_exit                       #
#input: actor_to_movies (db)                        #
#output: None                                       #
#function: outputs actor_to_movies to a file        #
#####################################################
def save_and_exit(actor_to_movies):
    path_out = "out.txt"      ###################################################
    if len(sys.argv) >=3:     #Ensures output file path is provided via sys.argv#
        path_out = sys.argv[2]###################################################
    os.chmod(path_out, 0o777)
    fout = open(path_out,"w")
    out_lines = []
    for actor,movies in actor_to_movies.items():
        #creates field list to stringify
        output = list([actor] + sorted(list(movies)))
        #adds comma-splitted field list to main line list
        out_lines.append(', '.join(output)+"\n")
    fout.writelines(sorted(out_lines))


#####################################################
#function name: read_menu                           #
#input: actor_to_movies (db)                        #
#output: None                                       #
#function: prints the menu, then inputs an option   #
#          and preforms it                          #
#####################################################
def read_menu(actor_to_movies):
    movie_to_actors = load_movie_to_actor(actor_to_movies)
    inp = 0
    while(inp not in range(4,5)):
        inp = int(\
        input("Please select an option:\n1) Query by movies \
        \n2) Query by actor\n3) Insert a new movie\n4) Save and Exit\n5) Exit\n"))
        if inp == 1:
            query_by_movies(movie_to_actors)
        elif inp == 2:
            query_by_actors(actor_to_movies,movie_to_actors)
        elif inp == 3:
            movie_to_actors = new_movie(movie_to_actors)
            #updates actor_to_movies and adds the new movie to it's actors and (if existing) new actors to it
            actor_to_movies=update_actor_to_movies(movie_to_actors,actor_to_movies)
        elif inp == 4:
            save_and_exit(actor_to_movies)
            break
        elif inp==5:
            break
        else:
            print("Error")


#####################################################
#function name: load_actor_to_movies                #
#input: f (file to read)                            #
#output: None                                       #
#function: load DB in the intuitive way-            #
#          actor:movies, via anexpression,          #
#          generates a dictionary.                  #
#####################################################
def load_actor_to_movies(f):
    # for each line: for each movie in line, create a list of movies and insert it with key- actor
    return {line.split(", ")[0]:set((movie.strip(" ") for movie in line.strip("\n \
    ").split(", ")[1:])) for line in f.readlines()}


#main Thread Entry point
if __name__ == "__main__":
    print("Processing...")
    movie_path = "movies.txt"   ##################################################
    if len(sys.argv)==3:        #Ensures input file path is provided via sys.argv#
        movie_path = sys.argv[1]##################################################
    else:
        print("Inputted "+str(len(sys.argv)-1)+" args, seems wrong...")
    fmovies = open(movie_path,"r")
    actor_to_movies = load_actor_to_movies(fmovies)
    read_menu(actor_to_movies)
