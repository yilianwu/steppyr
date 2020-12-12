from setuptools import setup, find_packages

setup(
    name="steppyr",
    version="1.0",
    author="Alan Gibson",
    author_email="alan.gibson@gmail.com",
    description="A stepper motor library in Python",
    long_description="""# A stepper motor library in Python\nThis API is based on [AccelStepper](http://www.airspayce.com/mikem/arduino/AccelStepper).\n""",
    long_description_content_type="text/markdown",
    keywords="servo motor library raspberry pi stepper",
    url="https://github.com/alangibson/steppyr",
    packages=find_packages(where='src'),
    package_dir={"": "src"},
    data_files=[('', ['README.md'])],
    install_requires=['RPi.GPIO', 'bokeh', 'spidev'],
    setup_requires=['pip'],
    classifiers=[
        "Programming Language :: Python :: 3",
    ],
)
