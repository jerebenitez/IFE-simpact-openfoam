import re
import json
import argparse, sys
from subprocess import Popen, PIPE
import jinja2


def trail(filename):
  return filename[:-2]


def get_file_library(filename):
    p = Popen(('find', '.', '-name', trail(filename) + '*', '-printf', '%h'), stdout=PIPE)
    output = p.communicate()[0] 
    return output.decode("utf-8")[2:] 


def get_deps(directory, filename, dependencies_file):
  text = ""
  with open(dependencies_file, "r") as rf:
    text = rf.read()
  
  pattern = "{}\.o :(.*)".format(filename[:-4])
  matches = re.findall(pattern, text)
  if matches:
    deps = matches[0].strip().split(" ")
    deps = list(map(get_file_library, deps))

    dir_dep = set(deps)
    directory["deps"] = dir_dep
    

def parse_directory(dictionary, directory, dependencies):
  dictionary.append({"name": directory["name"], "files": [], "deps": set(), "directories": []})
  current_directory = dictionary[-1]
  
  for content in directory["contents"]:
    if content["type"] == "file" and content["name"].endswith(("f90", "inc")):
      current_directory["files"].append(content["name"])
      get_deps(current_directory, content["name"], dependencies)
    
    if content["type"] == "directory":
      parse_directory(current_directory["directories"], content, dependencies)


def print_cmake(struc):
  templateLoader = jinja2.FileSystemLoader(searchpath="./")
  templateEnv = jinja2.Environment(loader=templateLoader, trim_blocks=True, lstrip_blocks=True)
  TEMPLATE_FILE = "cmake.template"
  template = templateEnv.get_template(TEMPLATE_FILE)

  for lib in struct:
    outputText = template.render(
      lib_name=lib["name"],
      sources=lib["files"],
      subdirectories=[x["name"] for x in lib["directories"]],
      link_libraries=lib["deps"]
    )
    print(outputText)


if __name__ == "__main__":
  parser = argparse.ArgumentParser()

  parser.add_argument('--deps', required=True, help='Archivo con listas de dependencias generadas con fort_depend.py')
  parser.add_argument('--tree', required=True, help='Árbol de directorios y archivos, generado con tree -J')

  args = parser.parse_args()

  struct = []
  with open(args.tree) as tree:
    data = json.load(tree)

    for d in data[0]["contents"]:
      if d["type"] == "directory":
        parse_directory(struct, d, args.deps)

  print_cmake(struct)


"""def parse_directory(directory):
  print('add_library({} "")'.format(d["name"]))
  print('target_sources({}\n\tPUBLIC'.format(d["name"]))
  for content in d["contents"]:
    if content["type"] == "file" and content["name"].endswith(("f90", "inc")):
      print("\t\t${{CMAKE_CURRENT_LIST_DIR}}/{}".format(content["name"]))
  print(")")"""
