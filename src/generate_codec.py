import os
import sys
import yaml
import shutil
import argparse
from jinja2 import Environment, FileSystemLoader

template_files = [ "tmpl.BOE_Msgs.cpp.jinja2", "tmpl.BOE_Encoder.cpp.jinja2", 
                   "tmpl.BOE_Decoder.cpp.jinja2", "tmpl.BOE_Stream.cpp.jinja2" ]

def get_details(config_file):
    details = config_file.upper().split('.')[0].split('_')
    return details[0], details[1], '_'.join(details[-3:])


def create_files(config_file, preview=False, create=False):
    # Load the YAML file
    with open(config_file, 'r') as file:
        yamlData = yaml.safe_load(file)

    exchange, protocol, version = get_details(config_file)

    base_dir = f'codecs/{exchange}/{protocol}/{version}'
    os.makedirs(os.path.dirname(f"{base_dir}/spec/{config_file}"), exist_ok=True)
    shutil.copy(config_file, f"{base_dir}/spec/{config_file}")
    
    env = Environment(loader=FileSystemLoader('./templates'), extensions=['jinja2.ext.do'])

    for template_file in template_files:
        template = env.get_template(template_file)
        output_file = f"{base_dir}/{template_file.split('.')[1]}.h"
        if preview:
            print(output_file)
        if create:
            os.makedirs(os.path.dirname(output_file), exist_ok=True)
            with open(output_file, 'w') as file:
                file.write(template.render(yamlData=yamlData))

def main():
    parser = argparse.ArgumentParser(
        description="Code generator for BOE protocol",
        epilog="Generate C++ code from YAML configuration"
    )
    
    parser.add_argument(
        "-c", "--config", required=True,
        help="YAML config of the spec"
    )
    parser.add_argument(
        "-n", "--preview", action="store_true",
        help="Preview the paths and files that will be generated"
    )
    parser.add_argument(
        "--create", action="store_true",
        help="Create the files and directories at the specified paths"
    )

    args = parser.parse_args()

    if not os.path.isfile(args.config):
        print(f"Error: Config file `{args.config}` does not exist.", file=sys.stderr)

    if args.create or args.preview:
        create_files(args.config, args.preview, args.create)

if __name__ == '__main__':
    main()