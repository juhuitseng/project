#!/usr/bin/python
# Vortex DDS project generator (for Community edition)


import os, sys, shutil


def main():
	if len(sys.argv) <= 1:
		print("Usage: ./ddsproject project_name")        
		exit(1)
	project_name = sys.argv[1]
	idl_filename = project_name + "Data.idl"
	global VORTEXPATH
	VORTEXPATH = os.environ['OSPL_HOME']
	if not VORTEXPATH:
		print("You have to source the release.com and set the correct OSPL_HOME first.")
		exit(1)
	# Check if the 'sample' directory exists or not
	if not os.path.exists('sample'):
		print("I need the 'sample' directory to generate the project files!")
		eixt(1)

	# Check if the target project directory exists or not
	if os.path.exists(project_name):
		print("The Project named:'{}'' was already exists. ".format(project_name))
		exit(1)

	# Check if the .idl file exists or not
	if not os.path.exists(idl_filename):
		print("The {}Data.idl file isn't exists!".format(project_name))
		exit(1)

	# start to create the project
	try:
		os.mkdir(project_name)
		os.makedirs(os.path.join(project_name, 'idl'))
		os.makedirs(os.path.join(project_name, 'src'))
		os.makedirs(os.path.join(project_name, 'standalone'))
		shutil.copy(idl_filename, os.path.join(project_name, 'idl'))
	except:
		print("Project generating fail...")
		exit(1)
	# copy sample source files into src directory
	generate_makefile_types(project_name)
	generate_makefile(project_name)
	shutil.copy('sample/src/CheckStatus.cpp', os.path.join(project_name, 'src'))
	shutil.copy('sample/src/CheckStatus.h', os.path.join(project_name, 'src'))
	shutil.copy('sample/src/DDSEntityManager.h', os.path.join(project_name, 'src'))
	shutil.copy('sample/src/DDSEntityManager.cpp', os.path.join(project_name, 'src'))
	generate_sourcefiles(project_name)
	generate_pub_sub_makefile(project_name)
	print("Project:{} has been successful generated!".format(project_name))
	return 
# the function to generate Makefile_sacpp_projectname_pub & Makefile_sacpp_projectname_sub
def generate_pub_sub_makefile(project_name):
	makefilename = 'Makefile.sacpp_{}_pub'.format(project_name.lower())
	# Modify the Makefile.sacpp_projectname_pub
	try:
		with open('sample/Makefile.sacpp_sample_pub', "r") as fp:
			content = fp.read()
			content = content.replace('%%NAME1%%', project_name.lower())
			content = content.replace('%%NAME2%%', project_name)
			content = content.replace('%%VORTEXPATH%%', VORTEXPATH)

			target_makefilename = os.path.join(os.path.join(project_name, 'standalone'), makefilename)
			with open(target_makefilename, 'w') as fpw:
				fpw.write(content)
	except:
		print("Project generating fail...(can't write the file)")
		exit(1)
	makefilename = 'Makefile.sacpp_{}_sub'.format(project_name.lower())
	# Modify the Makefile.sacpp_projectname_sub
	try:
		with open('sample/Makefile.sacpp_sample_sub', "r") as fp:
			content = fp.read()
			content = content.replace('%%NAME1%%', project_name.lower())
			content = content.replace('%%NAME2%%', project_name)
			content = content.replace('%%VORTEXPATH%%', VORTEXPATH)

			target_makefilename = os.path.join(os.path.join(project_name, 'standalone'), makefilename)
			with open(target_makefilename, 'w') as fpw:
				fpw.write(content)
	except:
		print("Project generating fail...(can't write the file)")
		exit(1)
	return 

# the function to generate Makefile_sacpp_projectname_types
def generate_makefile_types(project_name):
	makefilename = 'Makefile.sacpp_{}_types'.format(project_name.lower())
	# Modify the Makefile.sacpp_projectname_types
	try:
		with open('sample/Makefile.sacpp_sample_types', "r") as fp:
			content = fp.read()
			content = content.replace('%%NAME1%%', project_name.lower())
			content = content.replace('%%NAME2%%', project_name)
			content = content.replace('%%VORTEXPATH%%', VORTEXPATH)

			target_makefilename = os.path.join(os.path.join(project_name, 'standalone'), makefilename)
			with open(target_makefilename, 'w') as fpw:
				fpw.write(content)
	except:
		print("Project generating fail...(can't write the file)")
		exit(1)
	return 

def generate_makefile(project_name):
	try:
		with open('sample/Makefile.sample', 'r') as fp:
			content = fp.read()
			content = content.replace('%%PROJNAME%%', project_name.lower())
			target_makefilename = os.path.join(project_name, 'standalone/Makefile')
			with open(target_makefilename, 'w') as fpw:
				fpw.write(content)
	except:
		print("Project generating fail...(can't write the file)")
		exit(1)
	return 

def generate_sourcefiles(project_name):
	source_list = ['Publisher', 'Subscriber']
	for source in source_list:
		try:
			with open('sample/src/sampleData{}.cpp'.format(source)) as fp:
				content = fp.read()
				if os.path.exists('COMMUNITY'):
					content = '#define VORTEX_COMMUNITY\n' + content
				content = content.replace('HelloWorld', project_name)
				target_sourcefilename = os.path.join(project_name, 'src/{}Data{}.cpp'.format(project_name, source))
				with open(target_sourcefilename, 'w') as fpw:
					fpw.write(content)
		except:
			print("Project generating fail...(can't write the file)")
			exit(1)
	return 

if __name__ == "__main__":
	main()