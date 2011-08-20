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
const ScopeType GOOGLE_BUZZ = "https://www.googleapis.com/auth/buzz";
const ScopeType BOOK_SEARCH = "http://www.google.com/books/feeds/";
const ScopeType BLOGGER = "http://www.blogger.com/feeds/";
const ScopeType CALENDAR = "http://www.google.com/calendar/feeds";
const ScopeType CONTACTS = "https://www.google.com/m8/feeds/";
const ScopeType CHROME_WEB_STORE = "https://www.googleapis.com/auth/chromewebstore.readonly";
const ScopeType DOCUMENTS_LIST = "https://docs.google.com/feeds/";
const ScopeType FINANCE = "http://finance.google.com/finance/feeds/";
const ScopeType GMAIL = "https://mail.google.com/mail/feed/atom/";
const ScopeType HEALTH = "https://www.google.com/health/feeds/";
const ScopeType H9 = "https://www.google.com/h9/feeds/";
const ScopeType MAPS = "http://maps.google.com/maps/feeds/";
const ScopeType MODERATOR = "https://www.googleapis.com/auth/moderator";
const ScopeType OPENSOCIAL = "https://www-opensocial.googleusercontent.com/api/people/";
const ScopeType ORKUT = "https://orkut.gmodules.com/social/rest";
const ScopeType PICASA_WEB = "http://picasaweb.google.com/data";
const ScopeType SIDEWIKI = "http://www.google.com/sidewiki/feeds/";
const ScopeType SITES = "https://sites.google.com/feeds/";
const ScopeType SPREADSHEETS = "https://spreadsheets.google.com/feeds/";
const ScopeType TASKS = "http://www.googleapis.com/auth/tasks/";
const ScopeType URL_SHORTENER = "https://www.googleapis.com/auth/urlshortener";
const ScopeType WAVE = "http://wave.googleusercontent.com/api/rpc";
const ScopeType WEBMASTER_TOOLS = "http://www.google.com/webmasters/tools/feeds/";
const ScopeType YOUTUBE = "http://gdata.youtube.com";
}
}
}

#endif // QGDATAQTNESSGOAUTH_NAMESPACE_H
