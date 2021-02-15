SUMMARY = "Maintec"
SECTION = "celix"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "cacao curl openssl jansson libffi libxml2 zeromq czmq"

SRC_URI = "git://github.com/apache/celix.git;protocol=https;tag=rel/celix-${PV} \
           file://0001-Update-to-Cross-Compile-in-Yocto.patch"

S = "${WORKDIR}/git"

inherit cmake

EXTRA_OECMAKE = ""

INSANE_SKIP_${PN} += "useless-rpaths"
INSANE_SKIP_${PN}-dev += "dev-elf"