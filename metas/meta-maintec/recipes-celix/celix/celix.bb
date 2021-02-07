SUMMARY = "Maintec"
SECTION = "celix"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "cacao curl openssl jansson libffi libxml2 zeromq czmq"

SRCREV = "${AUTOREV}"

SRC_URI = "git://github.com/apache/celix.git;branch=master;protocol=https"

S = "${WORKDIR}/git"

inherit pkgconfig cmake

EXTRA_OECMAKE = ""