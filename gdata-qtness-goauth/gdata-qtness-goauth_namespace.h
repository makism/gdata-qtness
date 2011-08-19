#ifndef QGDATAQTNESSGOAUTH_NAMESPACE_H
#define QGDATAQTNESSGOAUTH_NAMESPACE_H

namespace GDataQtness {
namespace GOAuth {

enum ErrorCode {
    NoError = 200,
    BadRequest = 400,
    MissingScope = 1000
};

enum Version {
    VERSION_1_0,
    VERSION_2_0
};

enum SignatureMethod {
    HMAC_SHA1,
    RSA_SHA1
};

enum HttpMethod {
    POST,
    GET
};

namespace GoogleScope {
typedef QString ScopeType;

const ScopeType ANALYTICS = "https://www.google.com/analytics/feeds/";
const ScopeType GOOGLE_BASE = "http://www.google.com/base/feeds/";
const ScopeType GOOGLE_BUZZ = "";
const ScopeType BOOK_SEARCH = "http://www.google.com/books/feeds/";
const ScopeType BLOGGER = "http://www.blogger.com/feeds/";
const ScopeType CALENDAR = "http://www.google.com/calendar/feeds";
const ScopeType CONTACTS = "https://www.google.com/m8/feeds/";
const ScopeType CHROME_WEB_STORE = "";
const ScopeType DOCUMENTS_LIST = "https://docs.google.com/feeds/";
const ScopeType FINANCE = "http://finance.google.com/finance/feeds/";
const ScopeType GMAIL = "https://mail.google.com/mail/feed/atom/";
const ScopeType H9 = "https://www.google.com/health/feeds/";
const ScopeType MAPS = "http://maps.google.com/maps/feeds/";
const ScopeType MODERATOR = "";
const ScopeType OPENSOCIAL = "";
const ScopeType ORKUT = "";
const ScopeType PICASA_WEB = "http://picasaweb.google.com/data";
const ScopeType SIDEWIKI = "http://www.google.com/sidewiki/feeds/";
const ScopeType SITES = "https://sites.google.com/feeds/";
const ScopeType SPREADSHEETS = "https://spreadsheets.google.com/feeds/";
const ScopeType URL_SHORTENER = "";
const ScopeType WAVE = "";
const ScopeType WEBMASTER_TOOLS = "http://www.google.com/webmasters/tools/feeds/";
const ScopeType YOUTUBE = "http://gdata.youtube.com";
}
}
}

#endif // QGDATAQTNESSGOAUTH_NAMESPACE_H
