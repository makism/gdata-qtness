#include "fetchoauthrequesttoken.h"

FetchOAuthRequestToken::FetchOAuthRequestToken(QObject *parent) :
    QObject(parent)
{
    QUrl requestToken("https://www.google.com/accounts/OAuthGetRequestToken");
    QString hashKey("anonymous&");
    QByteArray signatureBaseString;
    QString normalizedHeader;

    QCA::init();

    QString oauth_header_data;
    QString oauth_consumer_key("anonymous");
    QString oauth_callback("oob");
    QString oauth_signature_method("HMAC-SHA1");
    QString oauth_version("1.0");
    QCA::InitializationVector iv(16);
    QByteArray oauth_nonce = iv.toByteArray().toHex();
    QString oauth_timestamp(QByteArray::number(QDateTime::currentDateTime().toTime_t()));
    QString oauth_signature;
    QString scope("https://www.google.com/analytics/feeds/");
    QString xoauth_displayname("xoauth_displayname=\"\"");


    //
    // Prepare url & header data.
    //
    oauth_header_data = oauth_header_data.append("oauth_callback=\"oob\",");
    oauth_header_data = oauth_header_data.append("oauth_consumer_key=\"anonymous\",");
    oauth_header_data = oauth_header_data.append("oauth_nonce=\"" + oauth_nonce + "\",");
    oauth_header_data = oauth_header_data.append("oauth_signature_method=\"HMAC-SHA1\",");
    oauth_header_data = oauth_header_data.append("oauth_timestamp=\"" + oauth_timestamp + "\",");
    oauth_header_data = oauth_header_data.append("oauth_version=\"1.0\"");

    qDebug() << "oauth_header_data\n" << oauth_header_data;


    normalizedHeader = oauth_header_data;
    normalizedHeader = normalizedHeader.replace("\"", "");
    normalizedHeader = normalizedHeader.replace(",", "&");
    QString tempScope(scope);
    normalizedHeader = normalizedHeader.append("&scope=" + tempScope.toUtf8().toPercentEncoding());

    //
    // Create signature digest.
    //
    signatureBaseString = "GET&";
    signatureBaseString = signatureBaseString.append(requestToken.toString().toUtf8().toPercentEncoding());
    signatureBaseString = signatureBaseString.append("&");
    signatureBaseString = signatureBaseString.append(normalizedHeader.toUtf8().toPercentEncoding());

    qDebug() << "\nSignature base string\n" << signatureBaseString;

    QByteArray key(hashKey.toUtf8());
    QCA::MessageAuthenticationCode hmac("hmac(sha1)", QCA::SymmetricKey(key));
    QCA::SecureArray array(signatureBaseString);
    hmac.update(array);
    QCA::SecureArray resultArray = hmac.final();
    QByteArray digest = resultArray.toByteArray().toBase64();

    oauth_signature = digest.toPercentEncoding();

    qDebug() << "\nSignature\n" << oauth_signature;

    //
    // Send data.
    //
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QNetworkRequest request;

    requestToken.addQueryItem("scope", scope);
    request.setUrl(requestToken);

    oauth_header_data = oauth_header_data.append(",oauth_signature=\"" + oauth_signature + "\"");
    oauth_header_data = QString("OAuth ").append(oauth_header_data);

    request.setRawHeader("Authorization", oauth_header_data.toUtf8());

    reply = manager->get(request);

    qDebug() << "\n\n";

    connect(reply, SIGNAL(readyRead()),
            this, SLOT(readyRead()));
}
