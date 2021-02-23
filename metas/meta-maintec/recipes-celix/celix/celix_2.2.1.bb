SUMMARY = "Maintec"
SECTION = "celix"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

DEPENDS += "cacao curl openssl jansson libffi libxml2 zeromq cppzmq"

SRC_URI = "git://github.com/apache/celix.git;protocol=https;tag=rel/celix-${PV} \
           file://0001-Update-to-Cross-Compile-in-Yocto.patch \
           file://0002-Update-to-Generate-Shared-Library-Version.patch"

S = "${WORKDIR}/git"

inherit pkgconfig cmake

EXTRA_OECMAKE = ""

INSANE_SKIP_${PN} += "useless-rpaths"