Name: resiprocate
Version: 1.10.1
Release: 1%{?dist}
Summary: SIP and TURN stacks, with SIP proxy and TURN server implementations
License: VSL
Url: http://www.resiprocate.org
Source: https://www.resiprocate.org/files/pub/reSIProcate/releases/%name-%version.tar.gz
BuildRequires: libtool automake autoconf
BuildRequires: asio-devel
BuildRequires: boost-devel
BuildRequires: cajun-jsonapi-devel
BuildRequires: c-ares-devel
BuildRequires: cppunit-devel
BuildRequires: gperf
%if 0%{?fedora} >= 18 || 0%{?rhel} >= 7
BuildRequires: db4-cxx-devel
%endif
%define use_systemd 0%{?fedora} >= 17 || 0%{?rhel} >= 7
%if %use_systemd
BuildRequires: systemd
%endif
BuildRequires: db4-devel
BuildRequires: openssl-devel >= 0.9.8
BuildRequires: mysql-devel
BuildRequires: pcre-devel
BuildRequires: perl
BuildRequires: popt-devel
BuildRequires: postgresql-devel
BuildRequires: python-devel
BuildRequires: python-pycxx-devel
%define use_freeradius_client 0%{?fedora} == 0 || 0%{?fedora} >= 21 || 0%{?rhel} >= 7
%if %use_freeradius_client
BuildRequires: freeradius-client-devel
%else
BuildRequires: radiusclient-ng-devel
%endif
BuildRequires: xerces-c-devel
Requires: openssl >= 0.9.8
%if %use_systemd
Requires(post): systemd
Requires(preun): systemd
Requires(postun): systemd
%else
Requires: chkconfig
Requires(preun): initscripts
%endif
Obsoletes: resiprocate-b2bua

%description
The reSIProcate components, particularly the SIP stack, are in use in both
commercial and open-source products. The project is dedicated to maintaining
a complete, correct, and commercially usable implementation of SIP and a few
related protocols.

%package libs
Summary: Shared libraries http://www.resiprocate.org

%description libs
reSIProcate is a framework that aims to fully implement the SIP protocol
in first class C++.  It is intended for use in other applications,
such as the repro SIP proxy.
This package provides the core libraries: librutil (utilities),
libresip (SIP stack/RFC compliant message parsing) and
libdum (SIP Dialog Usage Manager, a state machine for SIP dialogs).

%package devel
Summary: reSIProcate development files
Requires: %{name}-libs%{?_isa} = %{version}-%{release}

%description devel
Resiprocate SIP Stack development files.

%package repro
Summary: SIP proxy
Requires(pre): shadow-utils

%description repro
repro is the SIP proxy developed as part of the reSIProcate project.
It provides a high-quality, low maintenance solution for serving
small and large IP telephony installations.
reSIProcate is a framework that aims to fully implement the SIP protocol
in first class C++.  It is intended for use in other applications,
such as the repro SIP proxy.

%package turn-server
Summary: ICE/STUN/TURN server
Requires(pre): shadow-utils

%description turn-server
reTurn is the TURN server developed as part of the reSIProcate project.
TURN (RFC 5766) provides a standardised solution for VoIP applications
to find the most efficient way to route media streams when NAT and
firewall devices may be present.
reTurn provides a high-quality, low maintenance solution for serving
small and large IP telephony installations.  It has been used successfully
with a variety of SIP and Jabber applications, including Lumicall,
Jitsi, Empathy and Psi.
reSIProcate is a framework that aims to fully implement the SIP protocol
in first class C++.  It is intended for use in other applications,
such as the repro SIP proxy.

%package turn-server-psql
Summary: ICE/STUN/TURN server PostgreSQL users script
Requires: python-psycopg2

%description turn-server-psql
reTurn is the TURN server developed as part of the reSIProcate project.
This packages provides a Python script to synchronize the reTurn
users.txt file from a PostgreSQL table.

%package sipdialer
Summary: Click-to-call utility

%description sipdialer
sipdialer is a click-to-call application that uses the SIP REFER
method to force a SIP phone (for example, the phone on your desk)
to dial another number.  It can be registered in GConf to handle
clicks on sip:, sips: and tel: URIs in other applications and the
web browser.
reSIProcate is a framework that aims to fully implement the SIP protocol
in first class C++.  It is intended for use in other applications,
such as the repro SIP proxy.

%package clicktocall
Summary: Click-to-call server process

%description clicktocall
Provides a simple SIP click-to-call service.
reSIProcate is a framework that aims to fully implement the SIP protocol
in first class C++.  It is intended for use in other applications,
such as the repro SIP proxy.

%prep
%setup -q

%build
PYCONFIG=/usr/bin/python2.7-config
[ -x $PYCONFIG ] || PYCONFIG=/usr/bin/python2.6-config
if [ ! -x $PYCONFIG ] ; then echo "python*-config not found" ; exit 1 ; fi
%if %use_freeradius_client
RADIUS_CFG=--with-freeradius
%else
RADIUS_CFG=--with-radius
%endif
export LDFLAGS="${LDFLAGS} -L%{_libdir}/mysql -L%{_libdir}/libdb4"
CXXFLAGS="%{optflags} -I%{_includedir}/libdb4 -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS" %configure --with-c-ares --with-ssl --with-mysql --with-postgresql ${RADIUS_CFG} --with-repro --enable-repro-plugins --with-apps --enable-ipv6 --enable-dtls --with-python DEPS_PYTHON_CFLAGS="`${PYCONFIG} --cflags`" DEPS_PYTHON_LIBS="`${PYCONFIG} --ldflags`" PYCXX_SRCDIR=/usr/src/CXX/Python2 --enable-assert-syslog
sed -i 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' libtool
sed -i 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' libtool
make %{?_smp_mflags}

%install
make DESTDIR=%{buildroot} install
%if %use_systemd
install -p -D -m644 repro/pkg/common/repro.service %{buildroot}%{_unitdir}/repro.service
install -p -D -m644 reTurn/pkg/common/resiprocate-turn-server.service %{buildroot}%{_unitdir}/resiprocate-turn-server.service
%else
install -p -D -m755 repro/pkg/fedora/repro.init %{buildroot}%{_initddir}/repro
install -p -D -m755 reTurn/pkg/fedora/resiprocate-turn-server.init %{buildroot}%{_initddir}/resiprocate-turn-server
%endif
install -m 0755 -d %{buildroot}%{_sysconfdir}/repro
install -p -D -m640 repro/repro.config %{buildroot}%{_sysconfdir}/repro/repro.config
install -p -D -m640 repro/users.txt %{buildroot}%{_sysconfdir}/repro/users.txt
sed -i \
 -e 's!^#CAFile = /etc/pki/tls/cert.pem$!CAFile = /etc/pki/tls/cert.pem!' \
 -e 's!^LoggingType = cout$!LoggingType = syslog!' \
 -e 's!^LogLevel = INFO$!LogLevel = DEBUG!' \
 -e 's!^LogFilename = repro.log$!LogFilename = %{_localstatedir}/log/repro/repro.log!' \
 -e 's!^LogFileMaxBytes = 5242880!LogFileMaxBytes = 0!' \
 -e 's!^TlsDHParamsFilename = dh2048.pem!TlsDHParamsFilename = %{_sysconfdir}/repro/dh2048.pem!' \
 -e 's!^HttpAdminUserFile = users.txt$!HttpAdminUserFile = %{_sysconfdir}/repro/users.txt!' \
 -e 's!^#PluginDirectory = /usr/lib/repro/plugins$!PluginDirectory = %{_libdir}/resiprocate/repro/plugins!' \
 -e 's!^#RunAsUser = repro$!RunAsUser = repro!' \
 -e 's!^#RunAsGroup = repro$!RunAsGroup = repro!' \
 -e 's!^Daemonize = false$!Daemonize = true!' \
 -e 's!^Database1Path = ./$!Database1Path = %{_sharedstatedir}/repro!' \
 -e 's!^ChallengeThirdPartiesCallingLocalDomains = true$!ChallengeThirdPartiesCallingLocalDomains = false!' \
            %{buildroot}%{_sysconfdir}/repro/repro.config
install -p -D -m640 reTurn/reTurnServer.config %{buildroot}%{_sysconfdir}/reTurn/reTurnServer.config
install -p -D -m640 reTurn/users.txt %{buildroot}%{_sysconfdir}/reTurn/users.txt
sed -i -e 's/1234/6078a36f89704d83763c9e174b3e87a4/' %{buildroot}%{_sysconfdir}/reTurn/users.txt
sed -i \
 -e 's!^TlsTurnPort = 5349!TlsTurnPort = 0!' \
 -e 's!^LoggingType = file$!LoggingType = syslog!' \
 -e 's!^LogFilename = reTurnServer.log!LogFilename = %{_localstatedir}/log/reTurnServer/reTurnServer.log!' \
 -e 's!^LogFileMaxLines = 50000!LogFileMaxLines = 0!' \
 -e 's!^Daemonize = false!Daemonize = true!' \
 -e 's!^#RunAsUser = return!RunAsUser = return!' \
 -e 's!^#RunAsGroup = return!RunAsGroup = return!' \
 -e 's!^UserDatabaseFile = users.txt!UserDatabaseFile = %{_sysconfdir}/reTurn/users.txt!' \
 -e 's!^UserDatabaseHashedPasswords = false!UserDatabaseHashedPasswords = true!' \
 -e 's!^TlsTempDhFilename = dh2048.pem!TlsTempDhFilename = %{_sysconfdir}/reTurn/dh2048.pem!' \
            %{buildroot}%{_sysconfdir}/reTurn/reTurnServer.config
install -m 0755 -d %{buildroot}%{_sharedstatedir}/repro
rm -f %{buildroot}%{_libdir}/lib*.a
rm -f %{buildroot}%{_libdir}/lib*.la
rm -f %{buildroot}%{_libdir}/resiprocate/repro/plugins/lib*.a
rm -f %{buildroot}%{_libdir}/resiprocate/repro/plugins/lib*.la
install -m 0755 -d %{buildroot}/%{_docdir}/repro/examples/pyroute
install -p -D -m644 repro/plugins/pyroute/*.py %{buildroot}/%{_docdir}/repro/examples/pyroute
install -p -D -m644 repro/plugins/pyroute/README.txt %{buildroot}/%{_docdir}/repro/examples/pyroute

%pre repro
getent group repro >/dev/null || groupadd -r repro
getent passwd repro >/dev/null || \
    useradd -r -g repro -d %{_sharedstatedir}/repro -s /sbin/nologin \
    -c "repro SIP proxy" repro

%pre turn-server
getent group return >/dev/null || groupadd -r return
getent passwd return >/dev/null || \
    useradd -r -g return -d / -s /sbin/nologin \
    -c "reTurn TURN server" return

%post libs -p /sbin/ldconfig

%post repro
/sbin/ldconfig
%if %use_systemd
%systemd_post repro.service
%else
if [ $1 -eq 1 ] ; then
    # Initial installation
    /sbin/chkconfig --add repro
fi
%endif
if [ ! -e %{_sysconfdir}/repro/dh2048.pem ] ;
then
  /usr/bin/openssl dhparam -outform PEM -out %{_sysconfdir}/repro/dh2048.pem 2048
  chown root:repro %{_sysconfdir}/repro/dh2048.pem
  chmod 0640 %{_sysconfdir}/repro/dh2048.pem
fi

%post turn-server
%if %use_systemd
%systemd_post resiprocate-turn-server.service
%else
if [ $1 -eq 1 ] ; then
    # Initial installation
    /sbin/chkconfig --add resiprocate-turn-server
fi
%endif
if [ ! -e %{_sysconfdir}/reTurn/dh2048.pem ] ;
then
  /usr/bin/openssl dhparam -outform PEM -out %{_sysconfdir}/reTurn/dh2048.pem 2048
  chown root:return %{_sysconfdir}/reTurn/dh2048.pem
  chmod 0640 %{_sysconfdir}/reTurn/dh2048.pem
fi

%preun repro
%if %use_systemd
%systemd_preun repro.service
%else
if [ "$1" = 0 ]
then
   # Package removal, not upgrade
   /sbin/service repro stop
   /sbin/chkconfig --del repro
fi
%endif

%preun turn-server
%if %use_systemd
%systemd_preun resiprocate-turn-server.service
%else
if [ "$1" = 0 ]
then
   # Package removal, not upgrade
   /sbin/service resiprocate-turn-server stop
   /sbin/chkconfig --del resiprocate-turn-server
fi
%endif

%postun libs -p /sbin/ldconfig

%postun repro
/sbin/ldconfig
%if %use_systemd
%systemd_postun_with_restart repro.service
%else
if [ $1 -ge 1 ] ; then
    # Package upgrade, not uninstall
    /sbin/service repro try-restart
fi
%endif

%postun turn-server
%if %use_systemd
%systemd_postun_with_restart resiprocate-turn-server.service
%else
if [ $1 -ge 1 ] ; then
    # Package upgrade, not uninstall
    /sbin/service resiprocate-turn-server try-restart
fi
%endif

%clean
rm -rf $RPM_BUILD_ROOT

%files libs
%doc COPYING
%{_libdir}/libdum-*.so
%{_libdir}/librepro-*.so
%{_libdir}/libresip-*.so
%{_libdir}/libreTurnClient-*.so
%{_libdir}/librutil-*.so
%{_libdir}/libsipdial-*.so

%files devel
%dir %{_includedir}/clicktocall/
%dir %{_includedir}/reTurn/
%dir %{_includedir}/reTurn/client/
%dir %{_includedir}/repro/
%dir %{_includedir}/repro/monkeys/
%dir %{_includedir}/repro/stateAgents/
%dir %{_includedir}/resip/
%dir %{_includedir}/resip/dum/
%dir %{_includedir}/resip/dum/ssl/
%dir %{_includedir}/resip/stack/
%dir %{_includedir}/resip/stack/ssl/
%dir %{_includedir}/rutil/
%dir %{_includedir}/rutil/dns/
%dir %{_includedir}/rutil/ssl/
%dir %{_includedir}/rutil/stun/
%dir %{_includedir}/rutil/wince/
%dir %{_includedir}/sipdial/
%{_includedir}/clicktocall/*.hxx
%{_includedir}/reTurn/*.hxx
%{_includedir}/reTurn/client/*.hxx
%{_includedir}/repro/*.hxx
%{_includedir}/repro/*/*.hxx
%{_includedir}/resip/dum/*.hxx
%{_includedir}/resip/dum/ssl/*.hxx
%{_includedir}/resip/stack/*.hxx
%{_includedir}/resip/stack/ssl/*.hxx
%{_includedir}/rutil/*.hxx
%{_includedir}/rutil/*.h
%{_includedir}/rutil/*/*.hxx
%{_includedir}/sipdial/*.hxx
%{_libdir}/libdum.so
%{_libdir}/librepro.so
%{_libdir}/libresip.so
%{_libdir}/libreTurnClient.so
%{_libdir}/librutil.so
%{_libdir}/libsipdial.so

%files repro
%attr(0750,repro,repro) %dir %{_sharedstatedir}/repro
%attr(0640,root,repro) %config(noreplace) %{_sysconfdir}/repro/repro.config
%attr(0640,root,repro) %config(noreplace) %{_sysconfdir}/repro/users.txt
%config(missingok) %ghost %{_sysconfdir}/repro/dh2048.pem
%if %use_systemd
%{_unitdir}/repro.service
%else
%{_initddir}/repro
%endif
%{_sbindir}/repro
%{_sbindir}/reprocmd
%{_sbindir}/queuetostream
%{_mandir}/man8/repro*.8*
%dir %{_libdir}/resiprocate/repro/plugins
%{_libdir}/resiprocate/repro/plugins/*.so
%{_docdir}/repro

%files turn-server
%attr(0640,root,return) %config(noreplace) %{_sysconfdir}/reTurn/reTurnServer.config
%attr(0640,root,return) %config(noreplace) %{_sysconfdir}/reTurn/users.txt
%config(missingok) %ghost %{_sysconfdir}/reTurn/dh2048.pem
%dir %{_libdir}/resiprocate/reTurnServer
%if %use_systemd
%{_unitdir}/resiprocate-turn-server.service
%else
%{_initddir}/resiprocate-turn-server
%endif
%{_sbindir}/reTurnServer
%{_mandir}/man8/reTurnServer.8*

%files turn-server-psql
%{_libdir}/resiprocate/reTurnServer/psql-user-extract

%files sipdialer
%{_bindir}/sipdialer
%{_mandir}/man1/sipdialer.1*

%files clicktocall
%{_sbindir}/clicktocall

%changelog
* Sat Nov 24 2012 Daniel Pocock <daniel@pocock.pro> - 1.10.1-1
- Produce multiple packages for stack/libs, daemons, sipdialer
- Initial build based on autotools

