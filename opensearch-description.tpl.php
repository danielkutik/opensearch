<?php /* $Id$ */ ?>
<?xml version="1.0" encoding="UTF-8"?>
<OpenSearchDescription xmlns="http://a9.com/-/spec/opensearch/1.1/">
  <ShortName><?php print $shortname; ?></ShortName>
  <Description><?php print $description; ?></Description>
  <Contact><?php print $contact; ?></Contact>
  <Url type="text/html" template="<?php print $url_search; ?>"/>
  <Url type="application/rss+xml" template="<?php print $url_opensearch; ?>"/>
  <Url type="application/opensearchdescription+xml" rel="self" template="<?php print $url_self; ?>" />
  <?php if (!empty($tags)): ?>
    <Tags><?php print $tags; ?></Tags>
  <?php endif; ?>
  <?php if (!empty($longname)): ?>
    <LongName><?php print $longname; ?></LongName>
  <?php endif; ?>
  <?php if ($attribution): ?>
    <Attribution><?php print $attribution; ?></Attribution>
  <?php endif; ?>
  <?php if ($syndication_right): ?>
    <SyndicationRight><?php print $syndication_right; ?></SyndicationRight>
  <?php endif; ?>
  <AdultContent><?php print $adult_content; ?></AdultContent>
  <?php if (!empty($image_attributes)): ?>
    <Image<?php print $image_attributes; ?>><?php print $image_url; ?></Image>
  <?php endif; ?>
  <?php foreach ($languages as $language): ?>
    <Language><?php print $language->language; ?></Language>
  <?php endforeach; ?>
  <InputEncoding>UTF-8</InputEncoding>
  <OutputEncoding>UTF-8</OutputEncoding>
</OpenSearchDescription>