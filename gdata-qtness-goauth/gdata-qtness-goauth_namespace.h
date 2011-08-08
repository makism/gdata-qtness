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
const ScopeType GOOGLE_BASE = "https://www.google.com/analytics/feeds/";
const ScopeType GOOGLE_BUZZ = "https://www.google.com/analytics/feeds/";
const ScopeType BOOK_SEARCH = "https://www.google.com/analytics/feeds/";
const ScopeType BLOGGER = "https://www.google.com/analytics/feeds/";
const ScopeType CALENDAR = "https://www.google.com/analytics/feeds/";
const ScopeType CONTACTS = "https://www.google.com/analytics/feeds/";
const ScopeType CHROME_WEB_STORE = "https://www.google.com/analytics/feeds/";
const ScopeType DOCUMENTS_LIST = "https://www.google.com/analytics/feeds/";
const ScopeType FINANCE = "https://www.google.com/analytics/feeds/";
const ScopeType GMAIL = "https://www.google.com/analytics/feeds/";
const ScopeType H9 = "https://www.google.com/analytics/feeds/";
const ScopeType MAPS = "https://www.google.com/analytics/feeds/";
const ScopeType MODERATOR = "https://www.google.com/analytics/feeds/";
const ScopeType OPENSOCIAL = "https://www.google.com/analytics/feeds/";
const ScopeType ORKUT = "https://www.google.com/analytics/feeds/";
const ScopeType PICASA_WEB = "https://www.google.com/analytics/feeds/";
const ScopeType SIDEWIKI = "https://www.google.com/analytics/feeds/";
const ScopeType SITES = "https://www.google.com/analytics/feeds/";
const ScopeType SPREADSHEETS = "https://www.google.com/analytics/feeds/";
const ScopeType URL_SHORTENER = "https://www.google.com/analytics/feeds/";
const ScopeType WAVE = "https://www.google.com/analytics/feeds/";
const ScopeType WEBMASTER_TOOLS = "https://www.google.com/analytics/feeds/";
const ScopeType YOUTUBE = "https://www.google.com/analytics/feeds/";
}
}
}

#endif // QGDATAQTNESSGOAUTH_NAMESPACE_H
